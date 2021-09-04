
#include <logSystem.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LOG_LENGTH 150

static Log_Types current_type = Log_Type_None;

static const char * logNames[Log_Types_Len] = 
{
  [Log_Type_None] = "None",
  [Log_Type_Info] = "Info",
  [Log_Type_Warn] = "Warning",
  [Log_Type_Error] = "Error",
  [Log_Type_Critical] = "Critical",
};

none
set_log_level(Log_Types _type)
{
  current_type = _type;
};

i32
print(Log_Types _type, const char *_str)
{
  if (current_type <= _type)
    {
      if (strlen(_str) > MAX_LOG_LENGTH+20)
        return 2;
      printf("Log::%s: %s\n", logNames[_type], _str);
      return 1;
    }
  else
    return 0;
};

