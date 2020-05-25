#include "alien_actor.h"

#include "SDL.h"

#include "config.h"
#include "game.h"
#include "renderer.h"
#include "sdl_texture.h"
#include "texture_component.h"
#include "fence_component.h"
#include "bullet_actor.h"
#include "utility.h"


AlienActor::AlienActor(Game *game)
: Actor(game), reloadTime_(game->GetRandomAlienBulletReloadTime()) {
    side = Side::kAlien;
    // Create/Add move component
    auto mvCmp = std::make_unique<MoveComponent>(this);
    moveComp_ = mvCmp.get();
    components_.emplace_back(std::move(mvCmp));

    Renderer * renderer = game->GetRenderer();

    // Create/Add texture component
    SDLTexture *texture = renderer->GetTexture(Config::kEnemyImage);
    if (nullptr == texture) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL,
                       "Can't get texture!");
        return;
    }
    size.x = texture->GetWidth();
    size.y = texture->GetHeight();
    components_.emplace_back(std::make_unique<TextureComponent>(this, texture));

     // Create/Add fence component
    SDL_Rect rect{size.x*-2, 0, 0, 0};
    rect.w = renderer->GetScreenWidth() + size.x*2;
    screenHeight_ = renderer->GetScreenHeight();
    rect.h = screenHeight_;
    rect.h -= size.y;
    auto fence = std::make_unique<FenceComponent>(this);
    fence->fence = rect;
    components_.emplace_back(std::move(fence));
}

void AlienActor::Update() {
    Actor::Update();
    // Alien leave playground...
    if (position.x < -size.x) {
        isAlive = false;
        return;
    }
    // Alien bounce off
    if (position.y <= 0) {
        moveComp_->velocity.y = fabs(moveComp_->velocity.y);
    } else if (position.y >= screenHeight_ - size.y) {
        moveComp_->velocity.y = fabs(moveComp_->velocity.y)*-1.0f;
    }
    // Alien shoot
     if (--reloadTime_ <= 0) {
        FireBullet();
        reloadTime_ = game->GetRandomAlienBulletReloadTime();
    }
}

void AlienActor::SetVelocity(SDL_FPoint vel) {
    if (nullptr == moveComp_)
        return;
    moveComp_->velocity = vel;
}

void AlienActor::SetVelocity(float x, float y) {
    if (nullptr == moveComp_)
        return;
    moveComp_->velocity.x = x;
    moveComp_->velocity.y = y;
}

void AlienActor::FireBullet() {
    auto bullet = std::make_unique<BulletActor>(game, side);
    // Set bullet playground
    SDL_FPoint tgtPos{position};
    SDL_Point bulletSize = bullet->GetSize();
    tgtPos.x += (size.x / 2) - (bulletSize.x / 2);
	tgtPos.y += (size.y / 2) - (bulletSize.y / 2);
    bullet->SetPosition(tgtPos);

    // Set bullet velocity
    SDL_FPoint slope =  Utility::CalcSlope(tgtPos, game->GetPlayerRect());
    slope.x *= Config::kAlienBulletSpeed;
    slope.y *= Config::kAlienBulletSpeed;
    bullet->SetVelocity(slope.x, slope.y);

    // Add bullet to game
    game->AddBullet(std::move(bullet));
}
