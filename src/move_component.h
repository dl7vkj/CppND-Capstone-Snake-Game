#ifndef MOVE_COMPONENT_H
#define MOVE_COMPONENT_H

#include "SDL.h"

#include "component.h"
#include "actor.h"


class MoveComponent : public Component {
public:
    MoveComponent(GameObject *game_object) : Component(game_object) {}
    void Update() override {
        if (nullptr == owner)
            return;
        SDL_FPoint pos = owner->GetPosition();
        pos.x += velocity.x;
        pos.y += velocity.y;
        owner->SetPosition(pos);
    };

    // C.131: Avoid trivial getters and setters
    SDL_FPoint velocity{0, 0};
};


#endif // MOVE_COMPONENT_H
