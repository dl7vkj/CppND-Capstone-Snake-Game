#ifndef GAME_COMPONENTS_H
#define GAME_COMPONENTS_H

#include <vector>

#include "SDL2/SDL.h"

// #include "game.h"
// #include "game_object.h"

#include "component.h"

// RUBRIC: Classes follow an appropriate inheritance hierarchy.
// RUBRIC: Derived class functions override virtual base class functions.

class PlayerInputComponent : public InputComponent {
public:
    void Update(GameObject &obj, const uint8_t *keyboard_state) override;
};


class PlayerPhysicsComponent : public PhysicsComponent {
public:
    void Update(GameObject &obj, Game &game) override;
private:
    static constexpr int kReloadTime{8};
    int reload{0};
};


class AlienPhysicsComponent : public PhysicsComponent {
public:
    void Update(class GameObject &obj, class Game &game) override;

private:
    int reloadTime_{10};

    void FireBullet(class GameObject &obj, class Game &game);
};


class BulletPhysicsComponent : public PhysicsComponent {
public:
    void Update(GameObject &obj, Game &game) override;
};


class StarPhysicsComponent : public PhysicsComponent {
public:

    struct Star {
        float x;
        float y;
        float dx;
    };

    StarPhysicsComponent(Game &game);

    void Update(GameObject &obj, Game &game) override;

    std::vector<Star> &GetStars() { return stars_; }

private:
    std::vector<Star> stars_{};
    int screenWidth_;
};


class StarGraphicsComponent : public GraphicsComponent {
public:
    StarGraphicsComponent(StarPhysicsComponent *starPhyC_);

    void Update(class GameObject &obj, class Renderer &renderer) override;

private:
    StarPhysicsComponent *starPhyC_;
};


#endif // GAME_COMPONENTS_H
