#ifndef SWT__LOG_H
#define SWT__LOG_H

#include <swt.hpp>


/*!
 * \brief Logging limiters
 *
 * \details enum for limiting logs type
 */
enum class LogType {
  info,
  log,
  warn,
  error,
  critical,
};


/*!
 * \brief Current logging type
 */
static LogType current_type = LogType::warn; 

/*!
 * \brief Tries to print log if current_type highter than _type
 * \param[in] _type Log type
 * \param[in] _log Text to print
 */
void
print(LogType _type, const char * _log);

/*!
 * \brief Sets current log limit
 * \param[in] _type Logging type
 */
void
set_error_type(LogType _type);

#endif // SWT__LOG_H
