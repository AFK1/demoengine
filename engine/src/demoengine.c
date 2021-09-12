
#include <demoengine.h>
#include <stdio.h>
#include <ecs.h>
#include <render.h>

#ifdef EXAMPLE_MODULE
  #include <example.h>
#endif // EXAMPLE_MODULE

#ifdef LOGSYSTEM_MODULE
  #include <logsystem.h>
#else
  #include <nologsystem.h> // It's working!
#endif // LOGSYSTEM_MODULE

typedef struct Position_component
{
  Component _component;
  float x;
  float y;
  float z;
} Position_component;

CID position_component_id;
Scene * scene;
CID ball;

void
move_system(Component * _comp)
{
  Position_component * comp = (Position_component*) _comp;
  comp->x += 0x1p0;

  char log[0xFF];
  sprintf(log, "New position: %f %f %f", comp->x, comp->y, comp->z);

  print(Log_Debug, log);

  return;
};

int
main()
{
  // example module
#ifdef EXAMPLE_MODULE
  printf("Engine: example module used.\n");
  example_module_func();
#endif // EXAMPLE_MODULE

  // Logs
  set_loglevel(Log_Debug);
  print(Log_Debug,    "Debug message test");
  print(Log_Info,     "Info message test");
  print(Log_Warn,     "Warn message test");
  print(Log_Error,    "Error message test");
  print(Log_Critical, "Critical message test");

  // ECS
  scene = create_scene();
  set_scene(scene);
  ball = create_entity();
  position_component_id = reg_component();

  add_component(ball, 
      allocate_component(sizeof(Position_component)),
      position_component_id);

  add_system(move_system, position_component_id);

  for (unsigned int i = 0x0; i < 0xFF; i++)
    ecs_step();

  // Render
  void* win = render_init(500, 500);
  clear_win();
  swap_buf(win);

  // Game function
  return demomain();
};
