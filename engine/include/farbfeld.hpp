#ifndef __SWT_FARBFELD_H_
#define __SWT_FARBFELD_H_

#include <types.hpp>

/*!
 * RGBA color format struct
 */
struct RGBA
{
  u16 r; //< red
  u16 g; //< green
  u16 b; //< blue
  u16 a; //< alpha
};

/*!
 * Farbfeld format struct
 */
struct Farbfeld
{
  char magic[8]; //< Magic value
  u32 width; //< image width
  u32 height; //< Image height
  struct RGBA * data; //< Image data
};

/*!
 * Read farbfeld file
 *
 * @param[in] _path Path to file
 *
 * @return pointer to farbfeld struct
 */
struct Farbfeld *
readFarbfeld(const char * _path);

#endif // __SWT_FARBFELD_H_
