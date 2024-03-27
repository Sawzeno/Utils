#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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
  screen->resx    = resx;
  screen->resy    = resy;
  screen->string  = NULL; 
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
  newscreen->string  = parent->string + newScreenStart; 

  if (parent->horz == NULL) {
    parent->horz = newscreen;
  } else {
    Screen* temp = parent->horz;
    parent->horz = newscreen;
    parent->horz->horz  = temp; 
  }


  return newscreen;
}

Screen* splitVERT(Screen* parent, U64 percent){
  U64 parentsize  = parent->resy * parent->resx; 

  U64 disp = (parent->resx * percent) / 100;
  parent->resx  -= disp;

  U64 newScreenStart  = parentsize - (parent->resy * disp);

  Screen* newscreen = initScreen(disp, parent->resy);
  newscreen->string = parent->string + newScreenStart;

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

  window->memory  = malloc(sizeof(char) * window->resx * window->resy);

  Screen* screen  = initScreen(window->resx,  window->resy);
  screen->string  = window->memory;
  

  window->root = screen;

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

void render(Window* window){
  Screen* temp = window->root;
  while(temp != NULL){
    U64 i = 0;
    while(i < temp->resy){
      write(STDOUT_FILENO, temp->string + (temp->resx * i), temp->resx);
      write(STDOUT_FILENO, "\n" , 1);
      ++i;
    }
    temp  = temp->horz;
  }
}

