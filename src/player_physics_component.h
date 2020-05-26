#ifndef PLAYER_PHYSICS_COMPONENT_H
#define PLAYER_PHYSICS_COMPONENT_H

#include "physics_component.h"
#include "game_object.h"
#include "game.h"

class PlayerPhysicsComponent : public PhysicsComponent {
public:
    void Update(GameObject &obj, Game &game) override {
        // Move the object
        obj.x += obj.dx;
        obj.y += obj.dy;
        // Get the screen size
        int screen_w = game.GetRenderer().GetScreenWidth();
        int screen_h = game.GetRenderer().GetScreenHeight();
        int max_x = screen_w - obj.w;
        int max_y = screen_h - obj.h;

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

        if (--reload <= 0 && obj.fireBullet) {
            reload = kReloadTime;
            obj.fireBullet = false;
            float x = obj.x + obj.w;
            float y = obj.y + (obj.h / 2.0f);
            game.FireBullet(x, y, Config::kBulletSpeed, 0.0f,
                            GameObject::Side::kPlayer);
        }
    };

private:
    static constexpr int kReloadTime{8};
    int reload{0};
};


#endif // PLAYER_PHYSICS_COMPONENT_H
