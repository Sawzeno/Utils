#pragma once

#include <stdint.h>

#define FORMAT 19
#define TYPE 4
#define PI 3.14159265358979323846

typedef struct {
  uint8_t R;
  uint8_t G;
  uint8_t B;
  char* type;
  uint64_t size;
} Pixel;

typedef struct {
  char* string;
  uint64_t size;
} Buffer;


void fillBlueCircleOnRedBackground(Pixel* pixels, uint8_t H, uint8_t W, double centerX, double centerY, double radius) ;
void fill(Pixel* pixels, uint8_t H, uint8_t W) ;
Buffer* PixelBuffer(Pixel* pixels, uint8_t H, uint8_t W) ;
void draw();
