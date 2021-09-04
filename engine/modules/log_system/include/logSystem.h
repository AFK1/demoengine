
#ifndef __SWT_LOG_SYSTEM_H_
#define __SWT_LOG_SYSTEM_H_

#include <types.hpp>


/*!
 * Levels of logging
 */
typedef enum Log_Types
{
  Log_Type_None = 0, //< Don't print info at all
  Log_Type_Info, //< Debug information
  Log_Type_Warn, //< Warnings
  Log_Type_Error, //< Non-critical errors
  Log_Type_Critical, //< Critical errors
  Log_Types_Len, //< Don't use it
} Log_Types;


/*!
 * Set current log level
 *
 * @param[in] _type selected level
 *
 * @return Nothing
 */

none
set_log_level(Log_Types _type);


/*!
 * Print log information if log level
 * lower then selected type.
 *
 * @param[in] _type information level
 * @param[in] _str information
 *
 * @return 1 if printed, 0 if ignored,
 * 2 if log_limit is exceeded.
 */

i32
print(Log_Types _type, const char * _str);


#endif // __SWT_LOG_SYSTEM_H_
