#ifndef __DEMO_M_PHYSIC_H_
#define __DEMO_M_PHYSIC_H_

#include <demoengine.h>

typedef struct Mass_comp
{
  Component _comp;
  double mass;
} Mass_comp;

typedef struct Position_component
{
  Component _component;
  float x;
  float y;
  float z;
} Position_component;

extern CID pos_comp_id;
extern CID mass_comp_id;

void
init_physics();

#endif // __DEMO_M_PHYSIC_H_


