#include "texture_graphics_component.h"

#include "game_object.h"
#include "renderer.h"

void TextureGraphicsComponent::Update(GameObject &obj, Renderer &renderer) {
    if (nullptr == texture_)
        return;
    // NOTE: Adding 0.5 for rounding e.g. int(1.6 + 0.5) = 2
    texture_->Blit(obj.x + 0.5f, obj.y + 0.5f);
}
