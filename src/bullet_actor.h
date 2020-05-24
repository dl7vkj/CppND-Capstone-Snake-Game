#ifndef BULLET_ACTOR_H
#define BULLET_ACTOR_H

#include <cstdint>

#include "actor.h"
#include "move_component.h"


class BulletActor : public Actor {
public:
    BulletActor(Game *game);

    void Update() override;

private:
    MoveComponent *moveComp_{nullptr};
    uint16_t screenWidth;
};


#endif // BULLET_ACTOR_H
