#ifndef __DEMO_M_ECS_H_
#define __DEMO_M_ECS_H_

#define MAX_ECS_ARRAY 255

// Component identifier
typedef unsigned int CID;

typedef struct Component
{
  // Parent component ID
  CID related_id;
} Component;

typedef struct Entity
{
  // Entity unique ID
  CID id;
  // List of all components
  Component components[MAX_ECS_ARRAY];
} Entity;

typedef struct Scene
{
  /// ==== System part ====
  
  // Functions for components (aka systems)
  void (*systems_array[MAX_ECS_ARRAY])(Component *);

  // Systems arguments
  CID systems_args[MAX_ECS_ARRAY];

  // Systems array length.
  unsigned int systems_array_length;

  /// ==== Component part ====
  
  // All components
  Component* components_arrays[MAX_ECS_ARRAY];

  // Components array length
  CID components_array_length;
} Scene;

/*!
 * Add component to components list.
 * @param[in] _component component to add.
 * @return component ID in list.
 */
CID
add_component(Component * _component);

/*!
 * Add system to ECS loop.
 * @param[in] _system pointer to system function.
 * @param[in] _cid CID of component.
 */
void
add_system(void (*_system)(Component*), CID _cid);

/*!
 * Create new ECS scene.
 * @return Pointer to scene.
 */
Scene*
create_scene();

/*!
 * Set current scene.
 * @param[in] _scene Scene to make current.
 * @return Scene, if success.
 */
Scene*
set_scene(Scene* _scene);

/*!
 * Trying to get current scene and if can't create new.
 *
 * @return Current scene.
 *
 * @Warn This is always returns scene, 
 * even if it is dosen't exist yet.
 */
Scene*
get_scene();

/*!
 * Execute all systems in current scene.
 */
void
ecs_step();

#endif // __DEMO_M_ECS_H_
