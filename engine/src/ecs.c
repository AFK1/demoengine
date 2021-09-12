
#include <ecs.h>

#ifdef LOGSYSTEM_MODULE
#include <logsystem.h>
#else
#include <nologsystem.h>
#endif // LOGSYSTEM_MODULE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Scene * current_scene = NULL;

void
add_system(void (*_system)(Component*), CID _cid)
{
  get_scene()->systems_array
    [get_scene()->systems_array_length] = _system;
  get_scene()->systems_args
    [get_scene()->systems_array_length] = _cid;
  get_scene()->systems_array_length += 0x1;
  return;
};

CID
reg_component()
{
  return get_scene()->empty_cid++;
};

void
add_component(CID _ent, Component * _component, CID _cid)
{
  Entity * ent = get_entity(_ent);
  // Add component to entity.
  ent->components[ent->components_length] = 
    _component;
  ent->components_ids[ent->components_length++] = _cid;

  // Add component to scene components.
  get_scene()->components_arrays[_cid]
    [get_scene()->specific_components_length[_cid]++]
    = _component;
};

Component*
allocate_component(size_t _size, CID _ent)
{
  Component* comp = (Component*)
    malloc(_size);
  memset(comp, 0x0, _size);
  comp->related_id = _ent;
  return comp;
};

Scene*
create_scene()
{
  // Allocate scene.
  Scene * scene = (Scene*)
    malloc(sizeof(Scene));
  // Clear segment.
  memset(scene, 0x0, sizeof(Scene));
  if (current_scene == NULL)
    current_scene = scene;
  return scene;
};

Scene*
set_scene(Scene* _scene)
{
  if (_scene == NULL)
    return NULL;
  return current_scene = _scene;
};

Scene*
get_scene()
{
  if (current_scene == NULL)
    return set_scene(create_scene());
  return current_scene;
};

CID
create_entity()
{
  Entity * ent = (Entity*)
    malloc(sizeof(Entity));
  memset(ent, 0x0, sizeof(Entity));
  ent->id = get_scene()->entities_length;
  get_scene()->entities[get_scene()->entities_length++] = ent;

  return ent->id;
};

Entity *
get_entity(CID _id)
{
  return get_scene()->entities[_id];
};

Component *
get_entity_component(CID _ent, CID _cid)
{
  Entity * ent = get_entity(_ent);
  for (unsigned int i = 0x0; i <= ent->components_length; i++)
    {
      if (ent->components_ids[i] == _cid)
        return ent->components[i];
    };
  return NULL;
};

void
ecs_step()
{
  char log[0xFF];
  for (unsigned int i = 0x0; i < get_scene()->systems_array_length; i++)
    {
      for (unsigned int j = 0x0; 
          j < get_scene()->specific_components_length
            [get_scene()->systems_args[i]]; 
          j++)
        {
          (get_scene()->systems_array[i](
            get_scene()->components_arrays[
            get_scene()->systems_args[i]][j]));
        };
    };
};
