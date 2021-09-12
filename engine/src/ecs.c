
#include <ecs.h>

#ifdef LOGSYSTEM_MODULE
#include <logsystem.h>
#else
#include <nologsystem.h>
#endif // LOGSYSTEM_MODULE

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
  current_scene->systems_array_length += 1;
  return;
};

CID
reg_component()
{
  return current_scene->empty_cid++;
};

void
add_component(Entity * _ent, Component * _component, CID _cid)
{
  // Add component to entity.
  _ent->components[_ent->components_length++] = 
    _component;

  // Add component to scene components.
  current_scene->components_arrays[_cid]
    [current_scene->specific_components_length[_cid]++]
    = _component;
};

Scene*
create_scene()
{
  // Allocate scene.
  Scene * scene = (Scene*)
    malloc(sizeof(Scene));
  // Clear segment.
  memset(scene, 0, sizeof(Scene));
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

void
ecs_step()
{
  for (int i = 0; i < current_scene->systems_array_length; i++)
    {
      // TODO: execute all systems with all components.
    };
};
