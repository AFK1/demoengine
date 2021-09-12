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
  Component * components[MAX_ECS_ARRAY];

  // Length of components array.
  unsigned int components_length;
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

  // Smallest empty component id.
  CID empty_cid;
  
  // All components
  Component* components_arrays[MAX_ECS_ARRAY][MAX_ECS_ARRAY];

  // Components array length
  CID components_array_length;

  /// ==== Entity part ====

  // All entities on scene.
  Entity* entities[MAX_ECS_ARRAY];

  // Number of all entities.
  unsigned int entities_length;

} Scene;

/*!
 * Registers component in components list.
 * @return Empty CID for component.
 */
CID
reg_component();

/*!
 * Create new component by it's id.
 * @param[in] _cid ID of component in components list.
 * @return Pointer to component.
 */
Component*
create_component(CID _cid);

/*!
 * Adds component to entity.
 * @param[in] _ent entity to add component to.
 * @param[in] _cid ID of component to add.
 * @return Nothing.
 */
void
add_component(Entity* _ent, CID _cid);

/*!
 * Create new entity.
 */

/*!
 * Adds system to ECS loop.
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
