#include <swtebf.hpp>

int
main()
{
  SWT_Init();
  set_log_level(LogType::info);
  print(LogType::info, "Log test");
};
