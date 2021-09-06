#ifndef __DEMO_M_ECS_H_
#define __DEMO_M_ECS_H_

#define MAX_ECS_ARRAY 255

typedef unsigned int CID;

typedef struct Component
{
  // Parent component ID
  CID related_id;
} Component;

typedef struct Entity
{
  CID id;
  Component components[MAX_ECS_ARRAY];
} Entity;

typedef struct Scene
{
  // Functions for components (aka systems)
  void (*systems[MAX_ECS_ARRAY])(Component *);

  // Systems arguments
  CID systems_components[MAX_ECS_ARRAY];

  // All components
  Component* components[MAX_ECS_ARRAY];
} Scene;

/*!
 * Add component to components list.
 * @return component ID in list.
 * @param[in] _component component to add.
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

#endif // __DEMO_M_ECS_H_
