
#include <demoengine.h>
#include <stdio.h>

#ifdef EXAMPLE_MODULE
  #include <example.h>
#endif // EXAMPLE_MODULE

int
main()
{
#ifdef EXAMPLE_MODULE
  printf("Engine: example module used.\n");
  example_module_func();
#endif // EXAMPLE_MODULE
};
