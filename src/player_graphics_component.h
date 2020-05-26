#ifndef PLAYER_GRAPHICS_COMPONENT_H
#define PLAYER_GRAPHICS_COMPONENT_H

#include "graphics_component.h"
#include "sdl_texture.h"

class PlayerGraphicsComponent : public GraphicsComponent {
public:
    PlayerGraphicsComponent(SDLTexture *texture) : texture_(texture) {}
    void Update(class GameObject &obj, class Renderer &renderer) override;
private:
    SDLTexture *texture_;
};

#endif // PLAYER_GRAPHICS_COMPONENT_H
