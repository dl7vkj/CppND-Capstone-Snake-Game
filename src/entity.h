#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>

#include "SDL.h"

#include "sdl_texture.h"

class Entity {
public:
	Entity(SDLTexture &texture,
           std::size_t screen_width,
           std::size_t screen_height)
        : texture_(texture),
          screenWidth_(screen_width),
          screenHeight_(screen_height)
    {
        w = texture_.GetWidth();
        h = texture_.GetHeight();
        maxX_ = screenWidth_ - w;
        maxY_ = screenHeight_ - h;
    }
	virtual ~Entity() {}

	virtual void Render() const {
        if (health > 0) {
            texture_.Blit(x, y);
        }
    }

    virtual void Update() {
        x += dx;
		y += dy;
        if (x > screenWidth_ || x < -w) {
			health = 0;
		}
        if (y <= 0 || y >= maxY_) {
            dy = -dy;
        }
        y = y < 0 ? 0 : y > maxY_ ? maxY_ : y;
    }
	SDLTexture &GetTexture() { return texture_; }


    float x{0};
	float y{0};
    int w;
	int h;
	float dx{0};
	float dy{0};
	int health{0};
    int reload{0};
protected:
	SDLTexture &texture_;
    std::size_t screenWidth_;
    std::size_t screenHeight_;
    int maxX_;
    int maxY_;
};


#endif // ENTITY_H
