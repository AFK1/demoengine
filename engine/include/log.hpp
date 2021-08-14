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

static const char * LogName[] = {
  "Info",
  "Log",
  "Warn",
  "Error",
  "Critical"
};

static LogType current_type = LogType::warn;

void
print(LogType _type, const char * _log);

void
set_error_type(LogType _type);

#endif // SWT__LOG_H
