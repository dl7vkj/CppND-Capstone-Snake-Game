#include "bullet_actor.h"

#include "config.h"
#include "game.h"


BulletActor::BulletActor(Game *game)
    : Actor(game), screenWidth(game->GetRenderer()->GetScreenWidth()) {
    // Create/Add move component
    auto mvCmp = std::make_unique<MoveComponent>(this);
    moveComp_ = mvCmp.get();
    moveComp_->velocity.x = Config::kBulletSpeed;
    components_.emplace_back(std::move(mvCmp));

    Renderer * renderer = game->GetRenderer();

    // Create/Add texture component
    SDLTexture *texture = renderer->GetTexture(Config::kBulletImage);
    if (nullptr == texture) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL,
                       "Can't get texture!");
        return;
    }
    components_.emplace_back(std::make_unique<TextureComponent>(this, texture));
}

void BulletActor::Update() {
    Actor::Update();
    if (position.x > screenWidth) {
        isAlive = false;
    }
}
