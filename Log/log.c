#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<stdbool.h>
#include<unistd.h>

#include"log.h"

void sp(const char *format, ...) {
  va_list args;
  va_start(args, format);

  char *buffer;
  vasprintf(&buffer, format, args);
  va_end(args);

  MEMERR(buffer)
  printf("%s", buffer);

  free(buffer);
}

void writeint(U64 integer) {
  U64 _int = integer;

  U8 string[24]; 
  U8 count = 0;
  U8 rem = 0;

  do {
    rem = (U8)(_int % 10);
    string[count] = rem + '0';
    _int /= 10;
    ++count;
  } while (_int != 0);

  for (size_t i = count - 1; i >= 0; --i) {
    putchar(string[i]);
  }
  putchar('\n');
}

bool findstr(const char* str, const char* check) {
  ISNULL(str)
  ISNULL(check)
  if (*str == '\0' || *check == '\0') {
    LOG_WARNING("EMPTY string passed");
    return false;
  }

  return contains(str, check);
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
