#include "texture_component.h"

#include "game.h"

TextureComponent::TextureComponent(GameObject *game_object, SDLTexture *texture)
    : Component(game_object), texture_(texture) {
    owner->GetGame()->GetRenderer()->AddTextureComponent(this);
}

TextureComponent::~TextureComponent() {
    if (nullptr == owner)
        return;
    owner->GetGame()->GetRenderer()->RemoveTextureComponent(this);
}
