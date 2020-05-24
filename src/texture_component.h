#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H

#include "SDL.h"

#include "actor.h"
#include "component.h"
#include "sdl_texture.h"


class TextureComponent : public Component {
public:
    TextureComponent(GameObject &game_object) : Component(game_object), texture_(nullptr) {}
    void SetTexture(SDLTexture *texture) {
        texture_ = texture;
    }
    void Draw() {
        const SDL_FPoint &pos = owner.GetPosition();
        if (nullptr != texture_)
            texture_->Blit(pos.x, pos.y);
    }
private:
    SDLTexture *texture_;
};


#endif // TEXTURE_COMPONENT_H
