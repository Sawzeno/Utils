#include  <stdlib.h>
#include  <stdio.h>
#include  <unistd.h>
#include  "../Utils/Log/log.h"

typedef struct  Buffer Buffer;
typedef struct  Space  Space;
typedef struct  Window Window;
typedef  enum    Orient Oreint;

enum Oreint{
  HORZ,
  ENUM
};

struct Buffer{
  char*   memory;
  int     size;
};

struct Space{
  Space*  child;
  char*   string;
  char*   type;
  int     resx;
  int     resy;
};

struct Window{
  Buffer* buffer;
  Space*  rootspace;
  int     resx;
  int     resy;
};

Buffer* createBuffer(int size){
  Buffer* buffer  = malloc(sizeof(Buffer));
  buffer->size    = size;
  buffer->memory  = malloc(sizeof(char) * buffer->size);

  return buffer;
}

int fillspace(Space* space, char* type) {
  ISNULL(space)
  int size  = space->resx * space->resy;
  for (int i = 0; i < size; ++i) {
    space->string[i] = *type; 
  }
  return size; 
}

Space* splitSpace(Space* parent, int percentage, char* type) {
  int disp = (parent->resy * percentage) / 100; 
  parent->resy -= disp; 

  int parentSize = parent->resx * (parent->resy + disp); 
  int newSpaceStart = parentSize - (parent->resx * disp); 

  Space* newspace = malloc(sizeof(Space));
  newspace->string = parent->string + newSpaceStart; 
  newspace->resx = parent->resx;
  newspace->resy = disp;
  newspace->type = type;
  newspace->child = NULL;

  if (parent->child == NULL) {
    parent->child = newspace;
  } else {
    Space* temp = parent->child;
    parent->child = newspace;
    parent->child->child  = temp; 
  }

  fillspace(newspace, type);

  return newspace;
}

Window* createWindow(int resx , int resy , char* type){
  Window* window  = malloc(sizeof(Window));

  window->resx  = resx;
  window->resy  = resy;
  window->buffer  = createBuffer(resx * resy);

  Space* space  = malloc(sizeof(Space));
  space->string = window->buffer->memory;
  space->type   = type;
  space->resx   = resx;
  space->resy   = resy;
  space->child   = NULL;
  fillspace(space , type);

  window->rootspace = space;

  return window;
}

void resize(Space* parent ,int disp){

  Space* child  = parent->child;
  int limit     = parent->resy * child->resy;
  if(parent->resy + disp > limit || parent->resy + disp <= 0){
    perror("invalid disp");
  }

  parent->resy  += disp;
  child->resy   -=disp;

  child->string +=  (disp * parent->resx);
  
  fillspace(parent, parent->type);
  fillspace(child, child->type);
}

void render(Window* window){
  printf("BUFFER  : %s \x1b[2J\x1b[H \n" , window->buffer->memory);
  Space* temp = window->rootspace;
  int size;
  while(temp != NULL){
    int i = 0;
    while(i < temp->resy){
      write(STDOUT_FILENO, temp->string + (temp->resx * i), temp->resx);
      write(STDOUT_FILENO, "\n" , 1);
      ++i;
    }
    temp  = temp->child;
  }
}

int main(void){

  int resx  = 40;
  int resy  = 20;

  Window* window  = createWindow(resx , resy , "A");
  Space* spaceA = window->rootspace;
  Space* spaceB = splitSpace(spaceA, 50 , "B");
  Space* spaceC = splitSpace(spaceA , 50, "C");

  render(window);

  char input;
  read(STDIN_FILENO, &input, 1);
  switch (input) {
    case 'q':
      exit(EXIT_SUCCESS);
      break;
    case 'i':
      resize(spaceA, 1 );
      break;
    case  'd':
      resize(spaceA, -1);
      break;
  }

  render(window);
  return 0;
}
