#ifndef ALIEN_ACTOR_H
#define ALIEN_ACTOR_H

// #include <memory>

// #include "SDL_scancode.h"

#include "actor.h"
#include "move_component.h"


class AlienActor : public Actor {
public:
    AlienActor(Game *game);

    void Update() override;

    void SetVelocity(SDL_FPoint vel);
    void SetVelocity(float x, float y);

    void FireBullet();

private:
    MoveComponent *moveComp_{nullptr};
    int16_t reloadTime_;
    uint16_t screenHeight_{0};
};

#endif // ALIEN_ACTOR_H
