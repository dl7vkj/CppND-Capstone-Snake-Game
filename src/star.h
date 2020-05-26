#ifndef STAR_H
#define STAR_H

#include <cstdint>

#include "SDL.h"

#include "actor.h"
#include "move_component.h"


class Star : public GameObject {
public:
    Star(Game *game, float speed, int screen_width);

    void Update() override;

    float GetSpeed();

private:
    MoveComponent *moveComp_{nullptr};
    uint16_t screenWidth_;
};




#endif // STAR_H
