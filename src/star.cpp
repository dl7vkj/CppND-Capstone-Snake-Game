#include "star.h"

#include "game.h"
#include "star_component.h"


Star::Star(Game *game, float speed, int screen_width)
: GameObject(game), screenWidth_(screen_width) {
    // Create/Add move component
    auto mvCmp = std::make_unique<MoveComponent>(this);
    mvCmp->velocity.x = speed;
    moveComp_ = mvCmp.get();
    components_.emplace_back(std::move(mvCmp));

    // Create/Add star component
    components_.emplace_back(std::make_unique<StarComponent>(this));
}

void Star::Update() {
    GameObject::Update();
    if (position.x < -size.x) {
        position.x += screenWidth_;
    }
}

float Star::GetSpeed() {
    if (nullptr == moveComp_)
        return 0.0f;
    return moveComp_->velocity.x;
}
