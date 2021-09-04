
#include <logsystem.h>

#include <stdio.h>
#include <string.h>

static Log_Type l_current = Log_None;

const char * l_messages[Log_Type_Len] =
{
  [Log_Debug] = "Debug",
  [Log_Info] = "Info",
  [Log_Warn] = "Warn",
  [Log_Error] = "Error",
  [Log_Critical] = "Critical",
  [Log_None] = "None",
};

void
set_loglevel(Log_Type _level)
{
  l_current = _level;
};

int
print(Log_Type _level, const char * _str)
{
  if (_level < l_current)
    return 1;

  printf("%s: %s\n", l_messages[_level], _str);

  return 0;
};
