#include <log.hpp>
#include <iostream>

Log*
Log::getInstance()
{
  if (_instance == nullptr)
    _instance = new Log();
  return _instance;
}

void
Log::set_error_type(LogType _type) 
{
  _error_type = _type;
}

void
Log::print(LogType _type, const char * _log)
{
  if ((int)_error_type <= (int)_type)
    std::cout << "Log::" << LogName[(int)_type] << ": " << _log << std::endl;
}

Log::Log() {};

Log * Log::_instance = nullptr;
