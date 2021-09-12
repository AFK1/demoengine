
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
  current_scene->systems_array
    [current_scene->systems_array_length] = _system;
  current_scene->systems_args
    [current_scene->systems_array_length] = _cid;
  current_scene->systems_array_length += 0x1;
  return;
};

CID
reg_component()
{
  return current_scene->empty_cid++;
};

void
add_component(CID _ent, Component * _component, CID _cid)
{
  // Add component to entity.
  current_scene->entities[_ent]->components
    [current_scene->entities[_ent]->components_length++] = 
    _component;

  // Add component to scene components.
  current_scene->components_arrays[_cid]
    [current_scene->specific_components_length[_cid]++]
    = _component;
};

Component*
allocate_component(size_t _size)
{
  Component* comp = (Component*)
    malloc(_size);
  memset(comp, 0x0, _size);
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
  ent->id = current_scene->entities_length;
  current_scene->entities[current_scene->entities_length++] = ent;

  return ent->id;
};

void
ecs_step()
{
  char log[0xFF];
  for (unsigned int i = 0x0; i < current_scene->systems_array_length; i++)
    {
      for (unsigned int j = 0x0; 
          j < current_scene->specific_components_length
            [current_scene->systems_args[i]]; 
          j++)
        {
          (current_scene->systems_array[i](
            current_scene->components_arrays[
            current_scene->systems_args[i]][j]));
        };
    };
};
