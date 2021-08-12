#include <farbfeld.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <log.hpp>
#include <arpa/inet.h>
#include <string.h>

struct Farbfeld*
readFarbfeld(const char * _path)
{
  Log * logger = Log::getInstance();
  struct Farbfeld * res = (struct Farbfeld*) malloc(sizeof(struct Farbfeld));
  FILE * f = fopen(_path, "r");
  if (f == nullptr)
    {
      logger->print(LogType::error, "Can't open texture");
      return nullptr;
    };
  size_t readed = 0;
  
  fseek(f , 0 , SEEK_END);
  long fSize = ftell(f);
  rewind (f);

  if (fSize < sizeof(struct Farbfeld))
    {
      logger->print(LogType::error, "Empty texture");
      return nullptr;
    };

  uint8_t head[17];
  readed = fread(head, 1, sizeof(struct Farbfeld)-sizeof(struct Rgba *), f);
  if (readed != sizeof(struct Farbfeld)-sizeof(struct Rgba *))
    {
      logger->print(LogType::error, "Can't read texture");
      return nullptr;
    };
  memcpy(res->magicVal, head, 8);
  res->width = ntohl((head[8] << 0) | (head[9] << 8) | (head[10] << 16) | (head[11] << 24));
  res->height = ntohl((head[12] << 0) | (head[13] << 8) | (head[14] << 16) | (head[15] << 24));

// TODO: Add file size check
#if 0
#define byte2farsize(x) ( (x) /sizeof(struct Rgba))-sizeof(struct Farbfeld)+(sizeof(struct Rgba)*3)

  if (byte2farsize(fSize) != res->width*res->height)
    {
      logger->print(LogType::error, "Texture header does not match");
      char * buf = (char *) malloc(sizeof(char)*150);
      sprintf(buf, "sz of texture: %ld; in header: %lu", byte2farsize(fSize), res->width*res->height);
      logger->print(LogType::info, buf);
      return nullptr;
    };
#endif

  res->image = (struct Rgba*) malloc(sizeof(struct Rgba)*res->width*res->height);
  readed = fread(res->image, 1, sizeof(struct Rgba)*res->width*res->height, f);
  if (readed != sizeof(struct Rgba)*res->width*res->height)
    {
      logger->print(LogType::error, "Texture size error");
      return nullptr;
    };

  fclose(f);
  return res;
};
