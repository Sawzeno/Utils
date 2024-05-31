#pragma once

#include  <stdlib.h>
#include  <stdio.h>
#include  <unistd.h>

#include  "../Log/log.h"
#include  "../List/list.h"

typedef enum Orient {
  ROOT,
  HORZ,
  VERT
} Orient;

typedef struct Buffer Buffer;
typedef struct Row    Row;
typedef struct Screen Screen;
typedef struct Window Window;

struct Buffer {
  char*   str;
  U64     size;
};

struct Screen {
  Screen* vert;
  Screen* horz;  
  List*   rows;
  uint8_t id;
  U64     resx;
  U64     resy;
};

struct Window {
  char*   memory;
  Screen* root;
  U64     resx;
  U64     resy;
};

void*   initBuffer( char* str , U64 size);
void*   createBuffer(void* item);
void    debugBuffer(void* item);
Screen* splitHORZ   (Window* window , Screen* parent, U64 percent);
Screen* splitVERT   (Screen* parent, U64 percent);
Window* createWindow(U64 resx, U64 resy);
//void    resizeScreen(Screen* parent, Orient child ,I64 disp );
void    render      (Window* window);


