#ifndef __DEMO_M_ECS_H_
#define __DEMO_M_ECS_H_

#define MAX_ECS_ARRAY 255

typedef unsigned int CID;

typedef struct Entity
{
  CID id;
  void * components;
} Entity;

typedef struct Component
{
  // Parent component ID
  CID related_id;
} Component;

typedef struct Scene
{
  // Functions for components (aka systems)
  void (*systems[MAX_ECS_ARRAY])(void *);

  // Systems arguments
  CID systems_components[MAX_ECS_ARRAY];

  // All components
  Component* components[MAX_ECS_ARRAY];
} Scene;

#endif // __DEMO_M_ECS_H_
