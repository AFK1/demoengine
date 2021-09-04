#include <demoengine.hpp>

int
main()
{
  DEMO_Init();
  set_log_level(Log_Type_Info);
  print(Log_Type_Info, "Log test");
  struct Farbfeld* texture = readFarbfeld("test.ff");
  if (texture != NULL)
    {
      print(Log_Type_Info, (const char *)texture->magic);
    }
  else
    {
      print(Log_Type_Info, 
          "Please, place test.ff file into execution folder");
    };
  void* window = gl3_init();
  close_win(window);
  return 0;
};
