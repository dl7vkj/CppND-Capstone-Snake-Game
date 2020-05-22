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
        maxX_ = screenWidth_ - texture_.GetWidth();
        maxY_ = screenHeight_ - texture_.GetHeight();
        std::cout << "maxX=" << texture_.GetWidth() << " maxY=" << texture_.GetHeight() << "\n";
    }
	virtual ~Entity() {}
	virtual void Render() const {}
    virtual void Update() {}
	SDLTexture &GetTexture() { return texture_; }


    float x_{0};
	float y_{0};
	float dx_{0};
	float dy_{0};
	float health_{0};
	SDLTexture &texture_;
    std::size_t screenWidth_;
    std::size_t screenHeight_;
    int maxX_;
    int maxY_;
};


#endif // ENTITY_H
