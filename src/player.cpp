#include "player.h"

#include "SDL.h"

#include "config.h"
#include "game.h"
#include "renderer.h"
#include "sdl_texture.h"
#include "texture_component.h"
#include "fence_component.h"
#include "bullet_actor.h"


Player::Player(Game *game) : Actor(game) {
    // Create/Add move component
    auto mvCmp = std::make_unique<MoveComponent>(this);
    moveComp_ = mvCmp.get();
    components_.emplace_back(std::move(mvCmp));

    Renderer * renderer = game->GetRenderer();

    // Create/Add texture component
    SDLTexture *texture = renderer->GetTexture(Config::kPlayerImage);
    if (nullptr == texture) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL,
                       "Can't get texture!");
        return;
    }
    components_.emplace_back(std::make_unique<TextureComponent>(this, texture));

    // Create/Add fence component
    SDL_Rect rect{0, 0, 0, 0};
    rect.w = renderer->GetScreenWidth();
    rect.h = renderer->GetScreenHeight();
    rect.w -= texture->GetWidth();
    rect.h -= texture->GetHeight();
    auto fence = std::make_unique<FenceComponent>(this);
    fence->fence = rect;
    components_.emplace_back(std::move(fence));
}

void Player::FireBullet() {
    auto bullet = std::make_unique<BulletActor>(game);
    bullet->SetPosition(position);
    game->AddActor(std::move(bullet));
}
