#ifndef ALIEN_PHYSICS_COMPONENT_H
#define ALIEN_PHYSICS_COMPONENT_H

#include "physics_component.h"


class AlienPhysicsComponent : public PhysicsComponent {
public:
    void Update(class GameObject &obj, class Game &game) override {};
};


#endif // ALIEN_PHYSICS_COMPONENT_H
