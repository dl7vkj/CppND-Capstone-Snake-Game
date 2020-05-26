#ifndef TEXTURE_GRAPHICS_COMPONENT_H
#define TEXTURE_GRAPHICS_COMPONENT_H

#include "graphics_component.h"
#include "texture.h"

class TextureGraphicsComponent : public GraphicsComponent {
public:
    TextureGraphicsComponent(Texture *texture) : texture_(texture) {}
    void Update(class GameObject &obj, class Renderer &renderer) override;
private:
    Texture *texture_;
};

#endif // TEXTURE_GRAPHICS_COMPONENT_H
