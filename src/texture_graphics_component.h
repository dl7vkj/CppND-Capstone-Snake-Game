#ifndef TEXTURE_GRAPHICS_COMPONENT_H
#define TEXTURE_GRAPHICS_COMPONENT_H

#include "graphics_component.h"
#include "sdl_texture.h"

class TextureGraphicsComponent : public GraphicsComponent {
public:
    TextureGraphicsComponent(SDLTexture *texture) : texture_(texture) {}
    void Update(class GameObject &obj, class Renderer &renderer) override;
private:
    SDLTexture *texture_;
};

#endif // TEXTURE_GRAPHICS_COMPONENT_H
