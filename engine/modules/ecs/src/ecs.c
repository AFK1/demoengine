

#include <ecs.h>

#ifdef LOGSYSTEM_MODULE
#include <logsystem.h>
#else
#include <nologsystem.h>
#endif // LOGSYSTEM_MODULE

#include <stdlib.h>
#include <string.h>

static Scene * curr_scene = NULL;

CID
add_component(Component * _component)
{
  /*
   * current_scene->components[end] = _component;
   * return end;
   */
  curr_scene->comps[curr_scene->max_cid]
    = _component;
  return curr_scene->max_cid++;
};

void
add_system(void (*_system)(Component*), CID _cid)
{
  curr_scene->systems[curr_scene->max_sys] = _system;
  curr_scene->sys_comps[curr_scene->max_sys] = _cid;
  curr_scene->max_sys += 1;
  return;
};

Scene*
create_scene()
{
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
  return curr_scene = _scene;
};

Scene*
get_scene()
{
  if (curr_scene == NULL)
    return set_scene(create_scene());
  return curr_scene;
};
