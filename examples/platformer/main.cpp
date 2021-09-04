#include <farbfeld.hpp>
#include <logSystem.hpp>
#include <demoengine.hpp>

int
main()
{
  DEMO_Init();
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
  GLFWwindow* window = render_init();
  for(int n = 0;n<100;n++){}
  close_win(window);
  return 0;
};
