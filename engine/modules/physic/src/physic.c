#include <physic.h>
#include <stdio.h>
#include <logsystem.h>

CID pos_comp_id;
CID mass_comp_id;

void
gravity(Component * _comp) {
  //a = a - b * deltatime;     a-psition,  b-massa,  deltatime-can I use glfw gettime
  Mass_comp * mass = (Mass_comp*) _comp;
  Entity * ent = get_entity(mass->_comp.related_id);
  Position_component* pos = (Position_component*)
    get_entity_component(ent->id, pos_comp_id);

  if (pos == NULL)
    return;

  pos->y += mass->mass;
  return;
}

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

void
init_physics()
{
  mass_comp_id = reg_component();
  pos_comp_id = reg_component();
  add_system(gravity, mass_comp_id);
  add_system(move_system, pos_comp_id);
};
