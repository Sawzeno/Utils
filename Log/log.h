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

#define REACH fprintf(stderr, "\x1b[2;93mLINE: %d, FUNC: %s\x1b[0m\n", __LINE__, __func__);

typedef struct{
  uint8_t* string;
  uint8_t   size;
}UtilBuff;

UtilBuff* inttostr(uint64_t* integer);

