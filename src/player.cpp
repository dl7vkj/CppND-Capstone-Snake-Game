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
    side = Side::kPlayer;
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
    size.x = texture->GetWidth();
    size.y = texture->GetHeight();
    components_.emplace_back(std::make_unique<TextureComponent>(this, texture));

    // Create/Add fence component
    SDL_Rect rect{0, 0, 0, 0};
    rect.w = renderer->GetScreenWidth();
    rect.h = renderer->GetScreenHeight();
    rect.w -= size.x;
    rect.h -= size.y;
    auto fence = std::make_unique<FenceComponent>(this);
    fence->fence = rect;
    components_.emplace_back(std::move(fence));
}

void Player::ProcessInput(const uint8_t *keyboard_state) {
        Actor::ProcessInput(keyboard_state);
        moveComp_->velocity.x = 0.0f;
        moveComp_->velocity.y = 0.0f;
        if (keyboard_state[SDL_SCANCODE_UP]) {
            moveComp_->velocity.y = -4.0f;
        }
        if (keyboard_state[SDL_SCANCODE_DOWN]) {
            moveComp_->velocity.y = 4.0f;
        }
        if (keyboard_state[SDL_SCANCODE_LEFT]) {
            moveComp_->velocity.x = -4.0f;
        }
        if (keyboard_state[SDL_SCANCODE_RIGHT]) {
            moveComp_->velocity.x = 4.0f;
        }
        if (keyboard_state[SDL_SCANCODE_LCTRL]) {
            if (--reloadTime_ <= 0) {
                FireBullet();
                reloadTime_ = kReloadTime;
            }
        }
    }

void Player::FireBullet() {
    auto bullet = std::make_unique<BulletActor>(game, side);
    SDL_FPoint tgtPos;

    tgtPos.x = position.x + size.x;
    tgtPos.y = position.y + (size.y / 2) - (bullet->GetSize().y / 2);

    bullet->SetPosition(tgtPos);
    bullet->SetVelocity(Config::kBulletSpeed, 0.0f);
    game->AddBullet(std::move(bullet));
}
