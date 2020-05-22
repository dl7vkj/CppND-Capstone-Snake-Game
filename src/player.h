#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>
#include <iostream>

#include "config.h"
#include "sdl_texture.h"


class Player {
public:
    Player(SDLTexture &texture,
           std::size_t screen_width,
           std::size_t screen_height)
        : texture_(texture),
          screenWidth_(screen_width),
          screenHeight_(screen_height)
    {
        maxX_ = screenWidth_ - texture_.GetWidth();
        maxY_ = screenHeight_ - texture_.GetHeight();
        std::cout << "maxX=" << texture_.GetWidth() << " maxY=" << texture_.GetHeight() << "\n";
    }

    void SetPosition(int x, int y) {
        x_ = x;
        y_ = y;
    }
    void Render() const { texture_.Blit(x_, y_); }
    void Update() {
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

private:
    int x_{0};
    int y_{0};
    SDLTexture &texture_;
    std::size_t screenWidth_;
    std::size_t screenHeight_;
    int maxX_;
    int maxY_;
};


#endif // PLAYER_H
