#ifndef PLAYER_H
#define PLAYER_H

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
    void Render() const override { texture_.Blit(x, y); }
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


#endif // PLAYER_H
