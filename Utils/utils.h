#pragma once

#include  <stdio.h>
#include  <stdint.h>
#include  <signal.h>

#define LOG_WARN_ENABLED  1
#define LOG_INFO_ENABLED  1
#define LOG_TRACE_ENABLED 1
#define LOG_DEBUG_ENABLED 1

#define UASSERTIONS_ENABLED

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

typedef enum log_level{
  LOG_FATAL = 0,
  LOG_ERROR = 1,
  LOG_WARN  = 2,
  LOG_INFO  = 3,
  LOG_DEBUG = 4,
  LOG_TRACE = 5,
}log_level;

typedef struct  Unode Unode;
typedef struct  Ulist Ulist;  
typedef struct  Ubuff Ubuff;

#define UREPORT(X) Ulog(LOG_FATAL , "Assertion Failure \n'%s' \nfunc : %s \nfile : %s \nline : %d",#X,__FUNCTION__,__FILE__,__LINE__);

#define UFATAL(fmt, ...) do { Ulog(LOG_FATAL, fmt, ##__VA_ARGS__); } while(0);
#define UERROR(fmt, ...) do { Ulog(LOG_ERROR, fmt, ##__VA_ARGS__); } while(0);

#if LOG_WARN_ENABLED == 1
#define UWARN(fmt, ...) do { Ulog(LOG_WARN, fmt, ##__VA_ARGS__); } while(0);
#else
#define UWARN(fmt, ...)
#endif

#if LOG_INFO_ENABLED == 1
#define UINFO(fmt, ...) do { Ulog(LOG_INFO, fmt, ##__VA_ARGS__); } while(0);
#else
#define UINFO(fmt, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
#define UDEBUG(fmt, ...) do { Ulog(LOG_DEBUG, fmt, ##__VA_ARGS__); } while(0);
#else
#define UDEBUG(fmt, ...)
#endif

#if LOG_TRACE_ENABLED == 1
#define UTRACE(fmt, ...) do { Ulog(LOG_TRACE, fmt, ##__VA_ARGS__); } while(0);
#else
#define UTRACE(fmt, ...)
#endif

#ifdef UASSERTIONS_ENABLED
#define UASSERT(expr) if(expr){}else UREPORT(expr); raise(SIGILL);
#else
#define UASSERT(expr)
#endif

#define MEMERR(X) do { if(X == NULL) { UERROR("%s allocation failed", #X); exit(EXIT_FAILURE); } } while(0);

#define ISNULL(X) do { if(X == NULL) { UWARN("%s is NULL", #X); return 0; } } while(0);

struct  Ubuff{
  u8*     ptr;
  u64     len;
};

struct  Unode{
  void*   item;
  Unode*  next;
};

struct  Ulist{
  Unode* head;
  Unode* tail;
};

void    initLogging ();
void    killLogging ();
void    Ulog        (log_level level , const char* message , ...);
void    Uwrite      (const char *format , ...); 

u8*     readFile    (FILE* file);
void    writeint    (i64 integer);

Ubuff*  createUbuff (u8* ptr , u64 len);
void    freeUbuff   (void* item);

Unode*  createUnode (void* item);
Unode*  addUnode    (Ulist* ulist  , void* item);

Ulist*  createUlist ();
u64     freeUlist   (Ulist* ulist , void (*freeItem)(void*));

Ulist*  createWordList(u8* buffer); 
u64     printWordList (Ulist* list);

bool    contains (const char* str    , const char* check);
