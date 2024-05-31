#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include  <termios.h>
#include <stdio.h>

#include "window.h"
void* initBuffer(char* str, U64 size) {
  Buffer* buffer = malloc(sizeof(Buffer));
  MEMERR(buffer)
  buffer->str = str;
  buffer->size = size;

  return (void*)(buffer);
}

void* createColsItem(void* item, va_list args) {
  if (item == NULL) {
    return initBuffer(NULL, 0);
  } else {
    Buffer* buffer = (Buffer*)(item);
    return initBuffer(buffer->str, buffer->size);
  }
}

void debugColsItem(void* item) {
  Buffer* b = (Buffer*)item;
  if (b->str == NULL) {
    LOG_WARNING("STRING NULL");
  } else {
    write(STDOUT_FILENO, b->str, b->size);
    write(STDOUT_FILENO, "\n", 1);
  }
}

void* createRowItem(void* item, va_list args) {
  U64 size = va_arg(args, uint64_t);

  va_end(args);

  ListInfo* info = malloc(sizeof(ListInfo));
  MEMERR(info)
  info->createItemInfo = createColsItem;
  info->debugItemInfo = debugColsItem;

  List* colList = createList(info, size, NULL);
  return (void*)(colList);
}

void debugRowItem(void* item) {

  List* colList = (List*)item;
  if (colList == 0) {
    LOG_WARNING("NULL LIST");
  } else {
    debugList(colList);
  }
}

//-------------------------------------------------------

Screen* initScreen(U64 resx , U64 resy){

  Screen* screen  = malloc(sizeof(Screen));
  ISNULL(screen)
  screen->resx    = resx;
  screen->resy    = resy;
  screen->horz    = NULL;
  screen->vert    = NULL; 
  screen->rows    = NULL;
  return screen;
}

Screen* splitHORZ(Screen* parent, U64 percent) {
  U64 parentSize    = parent->resx * parent->resy; 
  U64 disp = (parent->resy * percent) / 100; 

  parent->resy -= disp; 
  U64 newScreenStart = parentSize - (parent->resx * disp); 

  Screen* newscreen  = initScreen(parent->resx, disp);

  if (parent->horz == NULL) {
    parent->horz = newscreen;
  } else {
    Screen* temp = parent->horz;
    parent->horz = newscreen;
    parent->horz->horz  = temp; 
  }


  return newscreen;
}

Screen* splitVERT(Window* window , Screen* parent, U64 percent){

  U64 disp = (parent->resx * percent) / 100;
  parent->resx  -= disp;
  Screen* newscreen = initScreen(disp, parent->resy);
  //------------------------------------------------------

  int id = findScreen(parent);
  

  //------------------------------------------------------
  if (parent->vert == NULL) {
    parent->vert = newscreen;
  } else {
    Screen* temp = parent->horz;
    parent->vert = newscreen;
    parent->vert->vert  = temp; 
  }

  return newscreen;
}

Window* createWindow(U64 resx , U64 resy){
  Window* window  = malloc(sizeof(Window));

  window->resx  = resx;
  window->resy  = resy;

  window->memory  = malloc(sizeof(char) * (window->resx + 1) * window->resy);
  ISNULL(window->memory)
  Screen* screen  = initScreen(window->resx,  window->resy);

  ListInfo* info  = createListInfo(createRowItem , debugRowItem);

  List* rowList = createList(info, window->resy, 0);

  char* memptr  = window->memory;
  for(U64 i = 0 ; i < rowList->size ; ++i){
    List* Row = (List*)(getListNode(rowList , i)->item);

    memset(memptr, '*', window->resx);
    void* buff  = initBuffer(memptr , window->resx);
    memptr  +=  window->resx;
    addListNode(Row, buff,NULL);

    memset(memptr, '\n', 1);
    void* end   = initBuffer(memptr , 1);
    strcpy(((Buffer*)end)->str, "\n");
    addListNode(Row , end , NULL);
    memptr += 1;
  }

  window->root = screen;
  // debugList(rowList);
  return window;
}

// void resizeScreen(Screen* parent ,Orient child , I64 disp){
//
//   Screen* vert  = parent->vert;
//   Screen* horz  = parent->horz;
//
//
//   U64 limit     = parent->resy * child->resy;
//   if(parent->resy + disp > limit || parent->resy + disp <= 0){
//     perror("invalid disp");
//   }
//
//   parent->resy  += disp;
//   child->resy   -=disp;
//
//   child->string +=  (disp * parent->resx);
//
//   fillScreen(parent, parent->type);
//   fillScreen(child, child->type);
// }
//
struct termios orig_termios;
void die(const char *s) {
  perror(s);
  exit(1);
}
void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    die("tcsetattr");
}
void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
  atexit(disableRawMode);
  struct termios raw = orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}
void render(Window* window){

  write(STDOUT_FILENO ,window->memory , (window->resx + 1) * window->resy);
  exit(EXIT_SUCCESS);
  enableRawMode();
  while (1) {
    char c = '\0';
    read(STDIN_FILENO, &c, 1);
    if (c == 'q') break;
    write(STDOUT_FILENO ,"\x1b[H" ,3);
  }
}

