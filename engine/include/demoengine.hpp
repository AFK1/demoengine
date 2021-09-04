#ifndef __EBFSWT_H_
#define __EBFSWT_H_

#include <types.hpp>

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
 * Init SWT engine
 */
none
SWT_Init();

/*!
 * Start SWT engine
 */
none
SWT_Loop();

#include <logSystem.hpp>

#include <farbfeld.hpp>

#endif
