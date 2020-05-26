#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H

#include "SDL.h"

#include "actor.h"
#include "render_component.h"
#include "texture.h"


class TextureComponent : public RenderComponent {
public:
    TextureComponent(GameObject *game_object, SDLTexture *texture);
    ~TextureComponent();
    void SetTexture(SDLTexture *texture) {
        texture_ = texture;
    }
    void Draw() override {
        if (nullptr == owner || nullptr == texture_)
            return;
        const SDL_FPoint &pos = owner->GetPosition();
        // NOTE: Adding 0.5 for rounding e.g. int(1.6 + 0.5) = 2
        texture_->Blit(pos.x + 0.5f, pos.y + 0.5f);
    }
private:
    SDLTexture *texture_;
};


#endif // TEXTURE_COMPONENT_H
