#pragma once

#include  <stdio.h>
#include  <stdint.h>
#include  <stdlib.h>
#include  <signal.h>
#include  <unistd.h>
#include  <stdbool.h>
#include  <time.h>
#include  <inttypes.h>
#include  <execinfo.h>
#include  <dlfcn.h>

typedef enum log_level {
  LOG_FATAL = 0,
  LOG_ERROR = 1,
  LOG_WARN = 2,
  LOG_INFO = 3,
  LOG_DEBUG = 4,
  LOG_TRACE = 5,
} log_level;

#ifndef LOG_WARN_ENABLED
#define LOG_WARN_ENABLED 1
#endif

#ifndef LOG_INFO_ENABLED
#define LOG_INFO_ENABLED  1
#endif

#ifndef LOG_TRACE_ENABLED
#define LOG_TRACE_ENABLED 1
#endif

#ifndef LOG_DEBUG_ENABLED
#define LOG_DEBUG_ENABLED 1
#endif

#define UREPORT(X) Ulog(LOG_ERROR, "%s  func : %s   file : %s line : %d", #X, __FUNCTION__, __FILE__, __LINE__);

#define UFATAL(fmt, ...) do { Ulog(LOG_FATAL, fmt, ##__VA_ARGS__); } while (0)
#define UERROR(fmt, ...) do { Ulog(LOG_ERROR, fmt, ##__VA_ARGS__); } while (0)

#if LOG_WARN_ENABLED == 1
#define UWARN(fmt, ...) do { Ulog(LOG_WARN, fmt, ##__VA_ARGS__); } while (0)
#else
#define UWARN(fmt, ...)
#endif

#if LOG_INFO_ENABLED == 1
#define UINFO(fmt, ...) do { Ulog(LOG_INFO, fmt, ##__VA_ARGS__); } while (0)
#else
#define UINFO(fmt, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
#define UDEBUG(fmt, ...) do { Ulog(LOG_DEBUG, fmt, ##__VA_ARGS__); } while (0)
#else
#define UDEBUG(fmt, ...)
#endif

#if LOG_TRACE_ENABLED == 1
#define UTRACE(fmt, ...) do { Ulog(LOG_TRACE, fmt, ##__VA_ARGS__); } while (0)
#else
#define UTRACE(fmt, ...)
#endif

#define UASSERTIONS_ENABLED

#ifdef UASSERTIONS_ENABLED
#define UASSERT(expr, ret, info) if (!(expr)) { UREPORT(expr); UERROR(info);return ret; }
#else
#define UASSERT(expr)
#endif

#define MEMERR(X) if (X == NULL) { UERROR("%s allocation failed", #X); exit(EXIT_FAILURE); }
#define ISNULL(X, Y) if (X == NULL) { UWARN("%s is NULL", #X); return Y; }



typedef uint64_t  u64;
typedef uint32_t  u32;
typedef uint16_t  u16;
typedef uint8_t   u8;

typedef int64_t   i64;
typedef int32_t   i32;
typedef int16_t   i16;
typedef int8_t    i8;

typedef float     f32;
typedef double    f64;

typedef struct Unode Unode;
typedef struct Ulist Ulist;
typedef struct Uinfo Uinfo;

struct  Uinfo{
  const char* str;
  bool        e;
};

struct  Unode{
  void*   item;
  Unode*  next;
};

struct  Ulist{
  Unode* head;
  Unode* tail;
};

void    initLogging (void);
void    sendSignal( int sig, const char* str, bool e);
void    Ulog        (log_level level , const char* message , ...);
void    Uwrite      (const char *format , ...); 

u8*     readFile    (FILE* file);
void    writeint    (i64 integer);

Unode*  createUnode (void* item, Unode* next);
Unode*  addUnode    (Unode* prev  , Unode* newUnode);

Ulist*  createUlist (void);
u64     freeUlist   (Ulist* ulist , void (*freeItem)(void*));


#define ADDUNODE(ulist, newUnode)\
ulist->tail = addUnode(ulist->tail, newUnode) \

#define INSERTUNODE(prev, newUnode)\
do{\
  Unode*  temp  = prev->next;\
  addUnode(prev, Unode);\
  addUnode(newUnode,temp);\
}while(0)

void initLogging(void) __attribute__((constructor));
