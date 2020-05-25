#ifndef FENCE_COMPONENT_H
#define FENCE_COMPONENT_H

#include "SDL.h"

#include "component.h"
#include "actor.h"


class FenceComponent : public Component {
public:
    FenceComponent(GameObject *game_object) : Component(game_object) {}
    void Update() override {
        if (nullptr == owner)
            return;
        SDL_FPoint pos = owner->GetPosition();

        if (pos.x < fence.x) {
            pos.x = fence.x;
        } else if (pos.x > fence.x + fence.w) {
            pos.x = fence.x + fence.w;
        }
        if (pos.y < fence.y) {
            pos.y = fence.y;
        } else if (pos.y > fence.y + fence.h) {
            pos.y = fence.y + fence.h;
        }
        owner->SetPosition(pos);
        // pos.x = pos.x < fence.x ? fence.x : pos.x > fence.x + fence.w ? fence.x + fence.w : pos.x;
        // pos.y = pos.y < fence.y ? fence.y : pos.y > fence.y + fence.h ? fence.y + fence.h : pos.y;
    };
    // C.131: Avoid trivial getters and setters
    SDL_Rect fence{0, 0, 0, 0};
    // bool bounceOff{false};
};


#endif // FENCE_COMPONENT_H
