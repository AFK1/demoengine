#ifndef __DEMO_M_EXAMPLE_H_
#define __DEMO_M_EXAMPLE_H_

typedef enum Log_Type
{
  Log_Debug = 0,
  Log_Info,
  Log_Warn,
  Log_Error,
  Log_Critical,
  Log_None,
  Log_Type_Len, //< Don't use it!
} Log_Type;


// Set current log level
void
set_loglevel(Log_Type _level);

/*!Print message with level
 *
 * @return 0 if printed, 1 if ignored.
 */
int
print(Log_Type _level, const char * _str);

#endif // __DEMO_M_EXAMPLE_H_
