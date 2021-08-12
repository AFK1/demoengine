#ifndef __FARBFELD_H_
#define __FARBFELD_H_

#include <stdint.h>

struct Rgba {
  uint16_t r;
  uint16_t g;
  uint16_t b;
  uint16_t a;
};

struct Farbfeld {
  char magicVal[8];
  uint32_t width;
  uint32_t height;
  struct Rgba * image;
};

struct Farbfeld*
readFarbfeld(const char * _path);

#endif // __FARBFELD_H_
