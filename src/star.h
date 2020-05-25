#ifndef STAR_H
#define STAR_H

#include <cstdint>

#include "SDL.h"

#include "game_object.h"
#include "move_component.h"


class Star : public GameObject {
public:
    Star(Game *game, float speed);

    void Update() override;

    float GetSpeed();

private:
    MoveComponent *moveComp_{nullptr};
    uint16_t screenWidth_;
};




#endif // STAR_H
