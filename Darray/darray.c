#include  "../Utils/utils.h"

enum{
  DARRAY_CAP,
  DARRAY_LEN,
  DARRAY_STRIDE,
  DARRAY_FIELD_LENGTH,
};

typedef struct Darray Darray;

void* createDarray(u64 len , u64 stride){
  u64 headersize  = DARRAY_FIELD_LENGTH * sizeof(u64);
  u64 arraysize   = len * stride;
  u64* newarray   = calloc(1 , arraysize + headersize);

  newarray[DARRAY_CAP]    = len;
  newarray[DARRAY_LEN]    = 0;
  newarray[DARRAY_STRIDE] = stride;

  return (void*)(newarray + DARRAY_FIELD_LENGTH);
}

void  destroyDarray(void* array){
  u64*  header  = (u64*)array - DARRAY_FIELD_LENGTH; 
  free(header);
}

int main(){
  u64*  array   = (u64*)createDarray(10, sizeof(u64));
  for(int i = 0 ; i < 10 ; ++i){
    array[i]  = 9;
  }

  for(int i = 0 ; i < 10 ; ++i){
    Uwrite("%"PRIu64"\n", array[i]);
  }
}

