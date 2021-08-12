#ifndef SWT__LOG_H
#define SWT__LOG_H

#include <swt.hpp>

enum class LogType {
  info,
  log,
  warn,
  error,
  critical,
};

class Log {
public:
  static Log* getInstance();
  Log(Log const&) = delete;
  void operator=(Log const&) = delete;
  
  void set_error_type(LogType _type); 
  void print(const char * _log);

private:
  static Log* _instance;
  Log();

  LogType _error_type;
};

#endif // SWT__LOG_H
