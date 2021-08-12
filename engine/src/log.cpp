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
Log::print(const char * _log)
{
  std::cout << (int)_error_type << ":" << _log << std::endl;
}

Log::Log() {};

Log * Log::_instance = nullptr;
