#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>
#include <iostream>

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
        x_ = x;
        y_ = y;
    }
    void Render() const override { texture_.Blit(x_, y_); }
    void Update() override {
        if (up){
			y_ -= 4;
		}
		if (down) {
			y_ += 4;
		}
		if (left) {
			x_ -= 4;
		}
		if (right) {
			x_ += 4;
		}
        x_ = x_ < 0 ? 0 : x_ > maxX_ ? maxX_ : x_;
        y_ = y_ < 0 ? 0 : y_ > maxY_ ? maxY_ : y_;
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
