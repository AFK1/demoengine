#include <logSystem.h>
#include <farbfeld.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <winsock.h>
#else
#include <arpa/inet.h>
#endif

struct Farbfeld *
readFarbfeld(const char *_path)
{
  struct Farbfeld * data = (struct Farbfeld *) 
    malloc(sizeof(struct Farbfeld));

  FILE * f_data = fopen(_path, "r");
  if (f_data == nullptr)
    {
      print(Log_Type_Error, "Can't load texture");
      return nullptr;
    };
  size_t readed = 0;

  fseek(f_data, 0, SEEK_END);
  long fileSize = ftell(f_data);
  rewind(f_data);

  if (fileSize < sizeof(struct Farbfeld))
    {
      print(Log_Type_Error, "Empty texture file");
      return nullptr;
    };

  // Reading header
  u8 *head = (u8*) malloc(sizeof(u8)*17);
  readed = fread(head, 1, sizeof(struct Farbfeld)-sizeof(struct RGBA*), f_data);
  if (readed != sizeof(struct Farbfeld)-sizeof(struct RGBA*))
    {
      print(Log_Type_Error, "Texture too small");
      return nullptr;
    };
  memcpy(data->magic, head, 8);
  data->width = ntohl((head[8] << 0) | (head[9] << 8) | (head[10] << 16) | (head[11] << 24));
  data->height = ntohl((head[12] << 0) | (head[13] << 8) | (head[14] << 16) | (head[15] << 24));

  data->data = (struct RGBA*) malloc(sizeof(struct RGBA)*data->width*data->height);
  readed = fread(data->data, 1, sizeof(struct RGBA)*data->width*data->height, f_data);
  if (readed != sizeof(struct RGBA)*data->width*data->height)
    {
      print(Log_Type_Error, "Texture size error");
      return nullptr;
    };

  fclose(f_data);
  free(head);
  return data;
};
