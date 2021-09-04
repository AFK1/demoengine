#ifndef __EBFSWT_H_
#define __EBFSWT_H_

#include <types.h>

typedef struct v3f
{
  float x;
  float y;
  float z;
} v3f;

typedef struct DemoObject
{
  v3f * Transform = nullptr;
} DemoObject;

/*!
 * Init Demo engine
 */
none
DEMO_Init();

/*!
 * Start Demo engine
 */
none
DEMO_Loop();

#include <logSystem.h>

#include <farbfeld.hpp>

#include <render.hpp>

#endif
