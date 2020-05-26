#ifndef PLAYER_PHYSICS_COMPONENT_H
#define PLAYER_PHYSICS_COMPONENT_H

#include "physics_component.h"


class PlayerPhysicsComponent : public PhysicsComponent {
public:
    void Update(class GameObject &obj, class Game &game) override {};
};


#endif // PLAYER_PHYSICS_COMPONENT_H
