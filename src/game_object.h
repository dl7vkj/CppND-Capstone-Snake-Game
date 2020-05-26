#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <memory>

#include "input_component.h"
#include "physics_component.h"
#include "graphics_component.h"

class GameObject {
public:
    enum Side{ kPlayer, kAlien, kNeutral};

    float x{0.0f};  // x position
    float y{0.0f};  // y position
    float dx{0.0f}; // x velocity
    float dy{0.0f}; // y velocity
    int w{0};       // width
    int h{0};       // height
    Side side{kNeutral};
    bool fireBullet{false};
    bool isAlive{true};
    int health{1};

    GameObject(std::unique_ptr<InputComponent> input,
               std::unique_ptr<PhysicsComponent> physics,
               std::unique_ptr<GraphicsComponent> graphics)
    : input_(std::move(input)),
      physics_(std::move(physics)),
      graphics_(std::move(graphics))
    {}

    void ProcessInput(const uint8_t *keyboard_state);
    void UpdatePhysics(class Game &game);
    void UpdateGraphics(class Renderer &renderer);

private:
    std::unique_ptr<InputComponent> input_;
    std::unique_ptr<PhysicsComponent> physics_;
    std::unique_ptr<GraphicsComponent> graphics_;
};


#endif // GAME_OBJECT_H
