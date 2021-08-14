#include <log.hpp>
#include <iostream>

void
set_error_type(LogType _type) 
{
  current_type = _type;
}

void
print(LogType _type, const char * _log)
{
  if ((int)current_type <= (int)_type)
    std::cout << "Log::" << LogName[(int)_type] << ": " << _log << std::endl;
}
