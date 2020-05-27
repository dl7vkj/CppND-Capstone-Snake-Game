#include "alien_physics_component.h"

void AlienPhysicsComponent::Update(class GameObject &obj, class Game &game) override {
    // Move the object
    obj.x += obj.dx;
    obj.y += obj.dy;
    // Alien killed
    if (obj.health <= 0) {
        obj.isAlive = false;
        return;
    }
    // Alien leave playground...
    if (obj.x < -obj.w) {
        obj.isAlive = false;
        return;
    }
    // Alien bounce off
    if (obj.y <= 0) {
        obj.dy = fabsf(obj.dy);
    } else if (obj.y >= game.GetRenderer().GetScreenHeight() - obj.h) {
        obj.dy = -fabsf(obj.dy);
    }
    // Alien shoot
    if (--reloadTime_ <= 0) {
        FireBullet(obj, game);
        reloadTime_ = game.GetRandomAlienBulletReloadTime();
    }
};

void AlienPhysicsComponent::FireBullet(class GameObject &obj, class Game &game) {
    float x = obj.x;
    float y = obj.y;
    x += (obj.w / 2);
    y += (obj.h / 2);

    // Set bullet velocity
    SDL_FPoint slope =  Utility::CalcSlope({x, y}, game.GetPlayerRect());
    slope.x *= Config::kAlienBulletSpeed;
    slope.y *= Config::kAlienBulletSpeed;
    game.FireBullet(x, y, slope.x, slope.y, GameObject::Side::kAlien);
}
