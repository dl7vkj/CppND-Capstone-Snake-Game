#ifndef BULLET_PHYSICS_COMPONENT_H
#define BULLET_PHYSICS_COMPONENT_H

#include "physics_component.h"


class BulletPhysicsComponent : public PhysicsComponent {
public:
    void Update(class GameObject &obj, class Game &game) override {};
};


#endif // BULLET_PHYSICS_COMPONENT_H
