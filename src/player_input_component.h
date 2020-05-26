#ifndef PLAYER_INPUT_COMPONENT_H
#define PLAYER_INPUT_COMPONENT_H

#include "input_component.h"
#include "game_object.h"

class PlayerInputComponent : public InputComponent {
public:
    void Update(GameObject &obj, const uint8_t *keyboard_state) override {
        obj.dx = 0.0f;
        obj.dy = 0.0f;
        if (keyboard_state[SDL_SCANCODE_UP]) {
            obj.dy = -4.0f;
        }
        if (keyboard_state[SDL_SCANCODE_DOWN]) {
            obj.dy = 4.0f;
        }
        if (keyboard_state[SDL_SCANCODE_LEFT]) {
           obj.dx = -4.0f;
        }
        if (keyboard_state[SDL_SCANCODE_RIGHT]) {
           obj.dx = 4.0f;
        }
        // if (keyboard_state[SDL_SCANCODE_LCTRL]) {
        //     if (--reloadTime_ <= 0) {
        //         FireBullet();
        //         reloadTime_ = kReloadTime;
        //     }
        // }
    }
};


#endif // PLAYER_INPUT_COMPONENT_H
