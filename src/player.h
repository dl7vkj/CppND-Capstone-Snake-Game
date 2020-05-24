#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include "SDL_scancode.h"

#include "actor.h"
#include "move_component.h"
//     if (event.repeat == 0) {
// 		if (event.keysym.scancode == SDL_SCANCODE_UP) {
// 			player.up = true;
// 		} else if (event.keysym.scancode == SDL_SCANCODE_DOWN) {
// 			player.down = true;
// 		} else if (event.keysym.scancode == SDL_SCANCODE_LEFT) {
// 			player.left = true;
// 		} else if (event.keysym.scancode == SDL_SCANCODE_RIGHT) {
// 			player.right = true;
// 		} else if (event.keysym.scancode == SDL_SCANCODE_LCTRL) {
//             player.fire = true;
//         }
// 	}
class Player : public Actor {
public:
    Player(Game *game) : Actor(game), moveComp_(this) {
        AddComponent(&moveComp_);
    }
    void ProcessInput(const uint8_t *keyboard_state) override {
        Actor::ProcessInput(keyboard_state);
        moveComp_.velocity.x = 0.0f;
        moveComp_.velocity.y = 0.0f;
        if (keyboard_state[SDL_SCANCODE_UP]) {
            moveComp_.velocity.y = -4.0f;
        }
        if (keyboard_state[SDL_SCANCODE_DOWN]) {
            moveComp_.velocity.y = 4.0f;
        }
        if (keyboard_state[SDL_SCANCODE_LEFT]) {
            moveComp_.velocity.x = -4.0f;
        }
        if (keyboard_state[SDL_SCANCODE_RIGHT]) {
            moveComp_.velocity.x = 4.0f;
        }
        if (keyboard_state[SDL_SCANCODE_LCTRL]) {
            // TODO: Fire
        }
    }
private:
    MoveComponent moveComp_;
};


#if 0
#include <cstdint>
#include <iostream>
#include <list>

#include "config.h"
#include "entity.h"
#include "sdl_texture.h"


class Player : public Entity {
public:
    Player(SDLTexture &texture,
           std::size_t screen_width,
           std::size_t screen_height)
        : Entity(texture, screen_width, screen_height)
    {}

    void SetPosition(int x, int y) {
        this->x = x;
        this->y = y;
    }
    void Render() const override {
        if (health)
            texture_.Blit(x, y);
    }
    void Update() override {
        dx = 0;
        dy = 0;

        if (reload > 0) {
            reload--;
        }

        if (up){
			dy = -Config::kPlayerSpeed;
		}
		if (down) {
			dy = Config::kPlayerSpeed;
		}
		if (left) {
			dx = -Config::kPlayerSpeed;
		}
		if (right) {
			dx = Config::kPlayerSpeed;
		}

        x += dx;
        y += dy;

        x = x < 0 ? 0 : x > maxX_ ? maxX_ : x;
        y = y < 0 ? 0 : y > maxY_ ? maxY_ : y;
    }

    bool up{false};
    bool down{false};
    bool left{false};
    bool right{false};
    bool fire{false};

private:
    // int x_{0};
    // int y_{0};
    // SDLTexture &texture_;
    // std::size_t screenWidth_;
    // std::size_t screenHeight_;
    // int maxX_;
    // int maxY_;
};
#endif

#endif // PLAYER_H
