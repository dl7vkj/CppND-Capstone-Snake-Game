#ifndef BULLET_ACTOR_H
#define BULLET_ACTOR_H

#include <cstdint>

#include "actor.h"
#include "move_component.h"


class BulletActor : public Actor {
public:
    BulletActor(Game *game, Side side);

    void Update() override;

    void SetVelocity(SDL_FPoint vel);
    void SetVelocity(float x, float y);

private:
    MoveComponent *moveComp_{nullptr};
    uint16_t screenWidth_;
    uint16_t screenHeight_;
};


#endif // BULLET_ACTOR_H
