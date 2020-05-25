#include "texture_component.h"

#include "game.h"

TextureComponent::TextureComponent(GameObject *game_object, SDLTexture *texture)
    : Component(game_object), texture_(texture) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Register texture component");
    owner->GetGame()->GetRenderer()->RegisterTextureComponent(this);
}

TextureComponent::~TextureComponent() {
    if (nullptr == owner)
        return;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Unregister texture component");
    owner->GetGame()->GetRenderer()->UnregisterTextureComponent(this);
}
