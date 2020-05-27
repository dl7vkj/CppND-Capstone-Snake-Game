#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "component.h"


class PhysicsComponent : public Component {
public:
    Type GetType() const final { return Component::Type::kPhysics; }

    virtual void Update(class GameObject &obj, class Game &game) = 0;
};


#endif // PHYSICS_COMPONENT_H
