
#include <logSystem.hpp>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LOG_LENGTH 150

static LogType current_type = LogType::none;

static const char * logNames[] = 
{
  "None",
  "Info",
  "Warning",
  "Error",
  "Critical",
};


none
set_log_level(LogType _type)
{
  current_type = _type;
};


i32
print(LogType _type, const char *_str)
{
  if ((int)current_type <= (int)_type)
    {
      if (strlen(_str) > MAX_LOG_LENGTH+20)
        return 2;
      printf("Log::%s: %s\n", logNames[(int)_type], _str);
      return 1;
    }
  else
    return 0;
};

