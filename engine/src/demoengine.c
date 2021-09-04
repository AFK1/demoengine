
#include <demoengine.h>
#include <stdio.h>

#ifdef EXAMPLE_MODULE
  #include <example.h>
#endif // EXAMPLE_MODULE

#ifdef LOGSYSTEM_MODULE
  #include <logsystem.h>
#endif // LOGSYSTEM_MODULE

int
main()
{
#ifdef EXAMPLE_MODULE
  printf("Engine: example module used.\n");
  example_module_func();
#endif // EXAMPLE_MODULE
#ifdef LOGSYSTEM_MODULE
  set_loglevel(Log_Debug);
  print(Log_Debug,    "Debug message test");
  print(Log_Info,     "Info message test");
  print(Log_Warn,     "Warn message test");
  print(Log_Error,    "Error message test");
  print(Log_Critical, "Critical message test");
#endif // LOGSYSTEM_MODULE
};
