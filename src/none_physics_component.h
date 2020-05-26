#ifndef NONE_PHYSICS_COMPONENT_H
#define NONE_PHYSICS_COMPONENT_H

#include "physics_component.h"


class NonePhysicsComponent : public PhysicsComponent {
public:
    void Update(class GameObject &obj[[maybe_unused]],
                class Game &game[[maybe_unused]]) override {};
};


#endif // NONE_PHYSICS_COMPONENT_H
