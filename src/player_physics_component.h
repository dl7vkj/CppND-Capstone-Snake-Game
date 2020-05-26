#ifndef PLAYER_PHYSICS_COMPONENT_H
#define PLAYER_PHYSICS_COMPONENT_H

#include "physics_component.h"
#include "game_object.h"
#include "game.h"

class PlayerPhysicsComponent : public PhysicsComponent {
public:
    PlayerPhysicsComponent(int obj_w, int obj_h, int screen_w, int screen_h)
    : max_x(screen_w - obj_w), max_y(screen_h - obj_h)
    {
    }

    void Update(GameObject &obj, Game &game) override {
        // Move the object
        obj.x += obj.dx;
        obj.y += obj.dy;
        // Get the screen size
        int w = game.GetRenderer().GetScreenWidth();
        int h = game.GetRenderer().GetScreenHeight();
        // Don't move outside the screen
        if (obj.x < 0) {
            obj.x = 0;
        } else if (obj.x > max_x) {
            obj.x = max_x;
        }
        if (obj.y < 0) {
            obj.y = 0;
        } else if (obj.y > max_y) {
            obj.y = max_y;
        }
    };

private:
    int max_x;
    int max_y;
};


#endif // PLAYER_PHYSICS_COMPONENT_H
