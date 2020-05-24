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
    // SDL_Point GetSize() {
    //     SDL_Point size{0,0};
    //     if (nullptr != texture_) {
    //         size.x = texture_->GetWidth();
    //         size.y = texture_->GetHeight();
    //     }
    // }
private:
    SDLTexture *texture_{nullptr};
};


#endif // TEXTURE_COMPONENT_H
