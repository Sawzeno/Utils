#include  <signal.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <stdarg.h>
#include  <stdbool.h>
#include  <unistd.h>
#include  <time.h>

#include  "utils.h"

static const char* logLevels[6]  = 
  { "[FATAL]: ",
    "[ERROR]: ",
    "[WARN]:  ",
    "[INFO]:  ",
    "[DEBUG]: ",
    "[TRACE]: "
  };

static const char* logColors[6] =
  {
    "\x1b[95m",
    "\x1b[91m",
    "\x1b[93m",
    "\x1b[90m",
    "\x1b[92m",
    "\x1b[97m"
  };

Unode*  createUnode(void* item, Unode* next) {
  Unode* unode = calloc(1 , sizeof(Unode)); 
  MEMERR(unode);
  unode->item = item; 
  unode->next = next;
  return unode;
}

Unode*  addUnode(Unode* prev, Unode* newUnode){
  ISNULL(prev , NULL);
  ISNULL(newUnode, NULL);
  prev->next  = newUnode;
  return newUnode;
}

Ulist*  createUlist(void){
  Ulist* ulist  = calloc(1 , sizeof(Ulist));
  MEMERR(ulist);
  Unode* dummy  = createUnode(NULL, NULL);
  ulist->head = ulist->tail = dummy;
  return ulist;
}

u64 freeUlist(Ulist* ulist , void (*freeItem)(void*)) {
  u64 items = 0;
  ISNULL(ulist , 0);

  Unode* curr = ulist->head;
  Unode* next = NULL;

  while (curr != NULL) {
    next = curr->next;
    if(freeItem != NULL){
      freeItem(curr->item); 
    }
    free(curr);
    curr = next;
    ++items;
  }

  free(ulist);
  return items;
}

void sendSignal( int sig, const char* str, bool e){
  union sigval sv;

  Uinfo* info = calloc(1, sizeof(Uinfo));
  MEMERR(info);
  info->str  = str;
  info->e    = e;
  sv.sival_ptr  = (void*)info;

  if (sigqueue(getpid(), sig, sv) == -1) {
    UFATAL("SIGQUEUE");
  }
}

void handle_sigill(int sig, siginfo_t* info, void* context){
  (void)context;
  if(sig  ==  SIGILL){
    if(info == NULL){
      UFATAL("SIGILL raised");
      exit(SIGILL);
    }else{
      Uinfo* uinfo  = (Uinfo*)(info->si_value.sival_ptr);
    
      UFATAL("SIGILL raised : %s", uinfo->str);
      if(uinfo->e){
        UFATAL("EXITING!");
        exit(SIGILL);
      }
    }
  }
}

void handle_sigint(int sig){
  if(sig == SIGINT){
    UFATAL("SIGINT, TERMINATING");
    exit(SIGINT);
  }
}
void handle_sigsegv(int sig){
  if(sig == SIGSEGV){
    void* buffer[100];
    u64 size  = backtrace(buffer,100);
    char** symbols  = backtrace_symbols(buffer, size);
    if(symbols != NULL){
        UERROR("func name : %s",symbols[4]);
    }else{
      UERROR("COULD NOT BACKTRACE SYMBOLS");
    }
    UFATAL("SIGSEGV: TERMINATING...");
    exit(SIGSEGV);
  }
}

void  initLogging (void){
  stack_t signalStack;
  signalStack.ss_sp = calloc(1,SIGSTKSZ);
  MEMERR(signalStack.ss_sp);
  signalStack.ss_size = SIGSTKSZ;
  signalStack.ss_flags= SS_ONSTACK;

  if(sigaltstack(&signalStack, NULL) == -1){
    UERROR("COULD NOT INITIALIZE SIGNALSTACK !");
    exit(EXIT_FAILURE);
  }

  struct sigaction sigactINT;
  sigemptyset(&sigactINT.sa_mask);
  sigactINT.sa_handler= handle_sigint;
  sigactINT.sa_flags = SA_ONSTACK;

  struct sigaction sigactSEGV;
  sigemptyset(&sigactSEGV.sa_mask);
  sigactSEGV.sa_handler= handle_sigsegv;
  sigactSEGV.sa_flags = SA_ONSTACK;

  struct sigaction sigactILL;
  sigemptyset(&sigactILL.sa_mask);
  sigactILL.sa_sigaction = handle_sigill;
  sigactILL.sa_flags  = SA_SIGINFO ;

  if( 
    sigaction(SIGINT, &sigactINT, NULL) == -1 ||
    sigaction(SIGSEGV,&sigactSEGV,NULL) == -1 ||
    sigaction(SIGILL, &sigactILL, NULL) == -1
  ){
    UERROR("COULD NOT SET UP SIGNAL HANDLERS");
    exit(EXIT_FAILURE);
  }
}

void  Ulog(log_level level , const char* message , ...){
  char out_message[1024];
  int  prefix_len = sprintf(out_message, "%s", logLevels[level]);
  va_list args;
  va_start(args , message);
  vsnprintf(out_message + prefix_len, 1024 - prefix_len, message , args);
  va_end(args);

  Uwrite("%s%s%s\n",logColors[level],out_message,"\x1b[0m");
}

void  Uwrite(const char *message, ...) {
  va_list args;
  va_start(args, message);
  char buffer[1024];
  u64 size  = vsnprintf(buffer,1024, message, args);
  va_end(args);

  write(STDOUT_FILENO, buffer, size); 
}

u8* readFile(FILE* file) {
  ISNULL(file , NULL);
  fseek(file, 0, SEEK_END);
  u64 fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  u8* fileBuffer = calloc(fileSize + 1, sizeof(u8)); 
  MEMERR(fileBuffer);

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


