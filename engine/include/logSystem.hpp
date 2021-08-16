
#ifndef __SWT_LOG_SYSTEM_H_
#define __SWT_LOG_SYSTEM_H_

#include <types.hpp>


/*!
 * Levels of logging
 */
enum class LogType
{
  none, //< Don't print info at all
  info, //< Debug information
  warn, //< Warnings
  error, //< Non-critical errors
  critical, //< Critical errors
};


/*!
 * Set current log level
 *
 * @param[in] _type selected level
 *
 * @return Nothing
 */

none
set_log_level(LogType _type);


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
print(LogType _type, const char * _str);


#endif // __SWT_LOG_SYSTEM_H_
