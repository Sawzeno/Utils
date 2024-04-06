//this contains an implimentation of a readonly list data strucuture that shall be used to only point and get info of strings

#include  <stdio.h>
#include  <stdlib.h>
#include  <stdarg.h>
#include  <stdbool.h>
#include  <unistd.h>
#include  <ctype.h>

#include  "log.h"

void up(const char *format, ...) {
  va_list args;
  va_start(args, format);

  char *buffer;
  U64 size  = vasprintf(&buffer, format, args);
  va_end(args);

  MEMERR(buffer)
  if (write(STDOUT_FILENO, buffer, size) == -1) {
    LOG_ERROR("Error writing to stdout");
  }

  free(buffer);
}

Ubuff* createUbuff(U8* ptr , U64 len){
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

U64 freeUlist(Ulist* ulist , void (*freeItem)(void*)) {
  U64 items = 0;
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


Ulist* createWordList(U8* buffer) {
  Ulist* list = createUlist();

  U8* wordStart = NULL;
  U64 wordSize = 0;

  U64 i = 0;
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

U64 printWordList(Ulist* list) {
  U64 num = 0;
  ISNULL(list)

  Unode* current = list->head;
  while (current != NULL) {
    Ubuff* word = (Ubuff*)current->item;
    up("%.*s\n", (int)word->len, word->ptr);
    ++num;
    current = current->next;
  }
  return num;
}

U8* readFile(FILE* file) {
  ISNULL(file)
  fseek(file, 0, SEEK_END);
  U64 fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  U8* fileBuffer = calloc(fileSize + 1, sizeof(U8)); 
  ISNULL(fileBuffer);

  U64 bytesRead = fread(fileBuffer, sizeof(U8), fileSize, file);
  if (bytesRead != fileSize) {
    free(fileBuffer);
    LOG_ERROR("error reading file");
  }

  fileBuffer[fileSize] = '\0'; 

  return fileBuffer;
}

void writeint(I64 integer) {
  bool isNegative = false;
  if (integer < 0) {
    isNegative = true;
    integer = -integer;
  }

  U64 _int = (U64)integer;

  U8 string[24];
  U8 count = 0;
  U8 rem = 0;

  do {
    rem = (U8)(_int % 10);
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
    LOG_WARNING("End of string reached prematurely");
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
