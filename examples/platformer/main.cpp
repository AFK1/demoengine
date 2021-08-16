#include "farbfeld.hpp"
#include "logSystem.hpp"
#include <swtebf.hpp>

int
main()
{
  SWT_Init();
  set_log_level(LogType::info);
  print(LogType::info, "Log test");
  struct Farbfeld* texture = readFarbfeld("test.ff");
  if (texture != nullptr)
    {
      print(LogType::info, (const char *)texture->magic);
    }
  else
    {
      print(LogType::info, 
	  "Please, place test.ff file into execution folder");
    };
  return 0;
};
