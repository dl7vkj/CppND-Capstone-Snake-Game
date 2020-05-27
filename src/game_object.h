#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <memory>
#include <vector>
#include <iostream>

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
    bool fireBullet{false}; // TODO: Remove
    bool isAlive{true};
    int health{1};

    GameObject();
    GameObject(std::unique_ptr<InputComponent> input,
               std::unique_ptr<PhysicsComponent> physics,
               std::unique_ptr<GraphicsComponent> graphics);
    virtual ~GameObject() {}

    void AddComponent(std::unique_ptr<InputComponent> comp);
    void AddComponent(std::unique_ptr<PhysicsComponent> comp);
    void AddComponent(std::unique_ptr<GraphicsComponent> comp);

    virtual void ProcessInput(const uint8_t *keyboard_state);
    virtual void UpdatePhysics(class Game &game);
    virtual void UpdateGraphics(class Renderer &renderer);

private:
    std::vector<std::unique_ptr<InputComponent>> inputComps_{};
    std::vector<std::unique_ptr<PhysicsComponent>> physicsComps_{};
    std::vector<std::unique_ptr<GraphicsComponent>> graphicsComps_{};
};


#endif // GAME_OBJECT_H
