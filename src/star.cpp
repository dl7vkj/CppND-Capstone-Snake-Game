#include "star.h"

#include "game.h"

Star::Star(Game *game, float speed)
: GameObject(game), screenWidth_(game->GetRenderer()->GetScreenWidth()) {
    // Create/Add move component
    auto mvCmp = std::make_unique<MoveComponent>(this);
    mvCmp->velocity.x = speed;
    moveComp_ = mvCmp.get();
    components_.emplace_back(std::move(mvCmp));
}

void Star::Update() {
    GameObject::Update();
    // Alien leave playground...
    if (position.x < -size.x) {
        position.x += screenWidth_;
    }
}

float Star::GetSpeed() {
    if (nullptr == moveComp_)
        return 0.0f;
    return moveComp_->velocity.x;
}
