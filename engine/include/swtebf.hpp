#ifndef __EBFSWT_H_
#define __EBFSWT_H_

#include <stdint.h>

typedef uint32_t u32;
typedef int32_t  i32;
typedef float    f32;
typedef double   f64;
typedef void *   any;
typedef void    none;

/*!
 * \brief Init SWT engine
 */
none
SWT_Init();

#endif
