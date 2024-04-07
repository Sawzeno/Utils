#include  <stdio.h>
#include  <stdlib.h>
#include  <stdarg.h>
#include  <stdbool.h>
#include  <unistd.h>
#include  <ctype.h>

#include  "utils.h"

void  initLogging (){
  Uwrite("TODO\n");
}

void  killLogging (){
  Uwrite("TODO\n");
}

void  Ulog(log_level level , const char* message , ...){
  const char* levels[6]  = {"[FATAL]: ","[ERROR]: ","[WARN]:  ","[INFO]:  ","[DEBUG]: ","[TRACE]: "};
  char out_message[1024];
  int  prefix_len = sprintf(out_message, "%s", levels[level]);
  va_list args;
  va_start(args , message);
  vsnprintf(out_message + prefix_len, 1024 - prefix_len, message , args);
  va_end(args);

  printf("%s\n",out_message);
}

void  Uwrite(const char *message, ...) {
  va_list args;
  va_start(args, message);
  char buffer[1024];
  u64 size  = vsnprintf(buffer,1024, message, args);
  va_end(args);

  write(STDOUT_FILENO, buffer, size); 
}

Ubuff* createUbuff(u8* ptr , u64 len){
  Ubuff*  ubuff = calloc(1 , sizeof(Ubuff));
  ISNULL(ubuff)
  ubuff->ptr  = ptr;
  ubuff->len  = len;
  return ubuff;
}

void freeUbuff(void* item){
  Ubuff* ubuff  = (Ubuff*)(item);
  free(ubuff);
}

Unode*  createUnode(void* item) {
  Unode* unode = calloc(1 , sizeof(Unode)); 
  ISNULL(unode) 
  unode->item = item; 
  return unode;
}

Ulist*  createUlist(){
  Ulist* ulist  = calloc(1 , sizeof(Ulist));
  ISNULL(ulist);
  return ulist;
}

Unode*  addUnode(Ulist* ulist  , void* item){
  ISNULL(ulist)
  if(ulist->head  == NULL){
    ulist->head = createUnode(item);
    ulist->tail = ulist->head;
  }else{
    ulist->tail->next = createUnode(item);
    ulist->tail = ulist->tail->next;
  }
  return ulist->tail;
}

u64 freeUlist(Ulist* ulist , void (*freeItem)(void*)) {
  u64 items = 0;
  ISNULL(ulist)

  Unode* curr = ulist->head;
  Unode* next = NULL;

  while (curr != NULL) {
    next = curr->next;
    freeItem(curr->item); 
    free(curr);
    curr = next;
    ++items;
  }

  free(ulist);
  return items;
}


Ulist* createWordList(u8* buffer) {
  Ulist* list = createUlist();

  u8* wordStart = NULL;
  u64 wordSize = 0;

  u64 i = 0;
  while (buffer[i] != '\0') {
    // Skip leading whitespace and newline characters
    while (isspace(buffer[i]) || buffer[i] == '\n') {
      ++i;
    }

    if (buffer[i] != '\0') {
      // Definitely at the start of a word
      wordStart = &buffer[i];
      wordSize = 0;

      while (buffer[i] != '\0' && !isspace(buffer[i]) && buffer[i] != '\n') {
        ++wordSize;
        ++i;
      }

      Ubuff*  word  = createUbuff(wordStart , wordSize); 
      addUnode(list, (void*)word);
    }
  }

  return list;
}

u64 printWordList(Ulist* list) {
  u64 num = 0;
  ISNULL(list)

  Unode* current = list->head;
  while (current != NULL) {
    Ubuff* word = (Ubuff*)current->item;
    Uwrite("%.*s\n", (int)word->len, word->ptr);
    ++num;
    current = current->next;
  }
  return num;
}

u8* readFile(FILE* file) {
  ISNULL(file)
  fseek(file, 0, SEEK_END);
  u64 fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  u8* fileBuffer = calloc(fileSize + 1, sizeof(u8)); 
  ISNULL(fileBuffer);

  u64 bytesRead = fread(fileBuffer, sizeof(u8), fileSize, file);
  if (bytesRead != fileSize) {
    free(fileBuffer);
    UERROR("error reading file");
    exit(EXIT_FAILURE);
  }

  fileBuffer[fileSize] = '\0'; 

  return fileBuffer;
}

void writeint(i64 integer) {
  bool isNegative = false;
  if (integer < 0) {
    isNegative = true;
    integer = -integer;
  }

  u64 _int = (u64)integer;

  u8 string[24];
  u8 count = 0;
  u8 rem = 0;

  do {
    rem = (u8)(_int % 10);
    string[count] = rem + '0';
    _int /= 10;
    ++count;
  } while (_int != 0);

  if (isNegative) {
    putchar('-');
  }

  for (size_t i = count; i > 0; --i) {
    putchar(string[i - 1]);
  }
  putchar('\n');
}

bool contains(const char* str, const char* check) {
  ISNULL(str)
  ISNULL(check)
  if (*str == '\0' && *check != '\0') {
    UWARN("End of string reached prematurely");
    return false;
  }

  if (*check == '\0') {
    return true;
  }

  if (*str == *check) {
    return contains(str + 1, check + 1);
  }

  return contains(str + 1, check);
}
