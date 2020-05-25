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

    // void ProcessInput(const uint8_t *keyboard_state) override {
    //     Actor::ProcessInput(keyboard_state);
    //     moveComp_->velocity.x = 0.0f;
    //     moveComp_->velocity.y = 0.0f;
    //     if (keyboard_state[SDL_SCANCODE_UP]) {
    //         moveComp_->velocity.y = -4.0f;
    //     }
    //     if (keyboard_state[SDL_SCANCODE_DOWN]) {
    //         moveComp_->velocity.y = 4.0f;
    //     }
    //     if (keyboard_state[SDL_SCANCODE_LEFT]) {
    //         moveComp_->velocity.x = -4.0f;
    //     }
    //     if (keyboard_state[SDL_SCANCODE_RIGHT]) {
    //         moveComp_->velocity.x = 4.0f;
    //     }
    //     if (keyboard_state[SDL_SCANCODE_LCTRL]) {
    //         FireBullet();
    //     }
    // }

    void FireBullet();

private:
    MoveComponent *moveComp_{nullptr};
    uint16_t screenHeight_{0};
};

#endif // ALIEN_ACTOR_H
