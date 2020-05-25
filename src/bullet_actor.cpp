#include "bullet_actor.h"

#include "config.h"
#include "game.h"


BulletActor::BulletActor(Game *game, Side side)
: Actor(game),
  screenWidth_(game->GetRenderer()->GetScreenWidth()),
  screenHeight_(game->GetRenderer()->GetScreenHeight()) {
    this->side = side;
    // Create/Add move component
    auto mvCmp = std::make_unique<MoveComponent>(this);
    moveComp_ = mvCmp.get();
    // moveComp_->velocity.x = Config::kBulletSpeed;
    components_.emplace_back(std::move(mvCmp));

    Renderer * renderer = game->GetRenderer();

    // Create/Add texture component
    SDLTexture *texture = nullptr;
    if (side == Side::kPlayer) {
        texture = renderer->GetTexture(Config::kBulletImage);
    } else {
        texture = renderer->GetTexture(Config::kAlienBulletImage);
    }

    if (nullptr == texture) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL,
                       "Can't get texture!");
        return;
    }
    size.x = texture->GetWidth();
    size.y = texture->GetHeight();
    components_.emplace_back(std::make_unique<TextureComponent>(this, texture));
}

void BulletActor::Update() {
    Actor::Update();
    if (health <= 0) {
        isAlive = false;
    }
    if (position.x > screenWidth_) {
        isAlive = false;
    } else if (position.x < 0.0f) {
        isAlive = false;
    }
    if (position.y > screenHeight_) {
        isAlive = false;
    } else if (position.y < 0.0f) {
        isAlive = false;
    }
}

void BulletActor::SetVelocity(SDL_FPoint vel) {
    if (nullptr == moveComp_)
        return;
    moveComp_->velocity = vel;
}

void BulletActor::SetVelocity(float x, float y) {
    if (nullptr == moveComp_)
        return;
    moveComp_->velocity.x = x;
    moveComp_->velocity.y = y;
}
