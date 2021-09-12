
#include <demoengine.h>
#include <stdio.h>
#include <ecs.h>
#include <render.h>

#ifdef EXAMPLE_MODULE
  #include <example.h>
#endif // EXAMPLE_MODULE

#ifdef PHYSIC_MODULE
  #include <physic.h>
#endif // PHYSIC_MODULE

#include <logsystem.h>

Scene * scene;
CID ball;

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

  init_physics();

  ball = create_entity();

  add_component(ball, 
      allocate_component(sizeof(Position_component), ball),
      pos_comp_id);
  add_component(ball,
      allocate_component(sizeof(Mass_comp), ball),
      mass_comp_id);

  ((Mass_comp*)get_entity_component(ball, mass_comp_id))->mass = 0x2p1;

  for (unsigned int i = 0x0; i < 0xFF; i++)
    ecs_step();

  Position_component * pos = (Position_component*)
    get_entity_component(ball, pos_comp_id);
  if (pos == NULL)
    {
      print(Log_Error, "Can't find position component in ball entity");
      return -0x1;
    };

  char log[0xFF];
  sprintf(log, "Current pos: %f %f %f", pos->x, pos->y, pos->z);
  print(Log_Debug, log);

  // Render
  void* win = render_init(500, 500);
  clear_win();
  swap_buf(win);

  // Game function
  return demomain();
};
