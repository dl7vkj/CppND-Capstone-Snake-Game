#ifndef BULLET_PHYSICS_COMPONENT_H
#define BULLET_PHYSICS_COMPONENT_H

#include "physics_component.h"


class BulletPhysicsComponent : public PhysicsComponent {
public:void Update(GameObject &obj, Game &game) override {
        // Move the object
        obj.x += obj.dx;
        obj.y += obj.dy;
        // Get the screen size
        int screen_w = game.GetRenderer().GetScreenWidth();
        int screen_h = game.GetRenderer().GetScreenHeight();

        if (obj.x > game.GetRenderer().GetScreenWidth()) {
            obj.isAlive = false;
        } else if (obj.x < -obj.w) {
            obj.isAlive = false;
        }
        if (obj.y > game.GetRenderer().GetScreenHeight()) {
            obj.isAlive = false;
        } else if (obj.y < -obj.h) {
            obj.isAlive = false;
        }
    };
};


#endif // BULLET_PHYSICS_COMPONENT_H
