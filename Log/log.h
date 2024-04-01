#pragma once

#include <stdint.h>

#define LOG_ERROR(fmt, ...) \
    fprintf(stderr, "[ERROR] %s: " fmt " [%s:%d]\n", __FUNCTION__, ##__VA_ARGS__, __FILE__, __LINE__);\
    exit(EXIT_FAILURE);\

#define LOG_WARNING(fmt, ...) \
    fprintf(stderr, "[WARNING] %s: " fmt " [%s:%d]\n", __FUNCTION__, ##__VA_ARGS__, __FILE__, __LINE__);\

#define MEMERR(X) if(X  ==  NULL){  \
        LOG_ERROR("%s allocation failed", #X);\
        }\

#define ISNULL(X) if(X  ==  NULL){\
        LOG_WARNING("%s is NULL",#X);\
          return 0;\
        }\

#define DEBUG write(STDOUT_FILENO, "\x1b[2;93mDEBUG\x1b[0m\n", 18);

#define REACH fprintf(stderr, "\x1b[2;93mFILE:  %s  LINE: %d  FUNC: %s\x1b[0m\n",__FILE__,__LINE__,__func__);

#define U64 uint64_t
#define U8	uint8_t

#define I64 int64_t
#define I8	int8_t

typedef struct{
  U8* string;
  U8  size;
}UtilBuff;

void writeint (U64 integer);
void sp       (const char *format , ...); 
bool findstr  (const char* str    , const char* check);
bool contains (const char* str    , const char* check);
