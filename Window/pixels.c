#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>

#include "pixels.h"

void fillBlueCircleOnRedBackground(Pixel* pixels, uint8_t H, uint8_t W, double centerX, double centerY, double radius) {
  for (size_t i = 0; i < H; ++i) {
    for (size_t j = 0; j < W; ++j) {
      double distance = sqrt(pow(i - centerY, 2) + pow(j - centerX, 2));
      if (distance <= radius) {
        pixels[j + (i * W)].R = 255;  
        pixels[j + (i * W)].G = 0;
        pixels[j + (i * W)].B = 0;
        pixels[j + (i * W)].type = "🮘";
      } else {
        pixels[j + (i * W)].R = 0;    
        pixels[j + (i * W)].G = 0;
        pixels[j + (i * W)].B = 255;
        pixels[j + (i * W)].type = "█";
      }
    }
  }
}

void fill(Pixel* pixels, uint8_t H, uint8_t W) {
  uint64_t mulitplierR = 255 / (H-1);
  uint64_t mulitplierG = 255 / (W-1);
  for (size_t i = 0; i < H; ++i) {
    for (size_t j = 0; j < W; ++j) {
      pixels[j + (i * W)].R = (i  * mulitplierR);
      pixels[j + (i * W)].G = (j  * mulitplierG) ;
      pixels[j + (i * W)].B = 0;
      pixels[j + (i * W)].type = "█";
    }
  }
}

Buffer* PixelBuffer(Pixel* pixels, uint8_t H, uint8_t W) {
  uint64_t stride = FORMAT + TYPE;
  uint64_t size = stride * H * W;

  Buffer* buffer = malloc(sizeof(Buffer));
  buffer->string = malloc(size);

  size_t index = 0;
  for (size_t i = 0; i < H; ++i) {
    for (size_t j = 0; j < W; ++j) {
      index += sprintf(buffer->string + index, "\x1b[38;2;%d;%d;%dm%s",
                       pixels[j + (i * W)].R, pixels[j + (i * W)].G,
                       pixels[j + (i * W)].B, pixels[j + (i * W)].type);
    }
    index += sprintf(buffer->string + index, "\n");
  }

  buffer->size = size;

  return buffer;
}

void draw() {

  uint8_t H = 28;
  uint8_t W = 56;
  Pixel* pixels = malloc(sizeof(Pixel) * H * W);

  double centerX = W / 2.0;
  double centerY = H / 2.0;
  double radius = fmin(centerX, centerY) - 1.0;

  fillBlueCircleOnRedBackground(pixels, H, W, centerX, centerY, radius);

  Buffer* pixelBuffer = PixelBuffer(pixels, H, W);

  write(STDOUT_FILENO , "\x1b[2J\x1b[H",7);
  write(STDOUT_FILENO , pixelBuffer->string , pixelBuffer->size);

  free(pixels);
  free(pixelBuffer->string);
  free(pixelBuffer);
}

