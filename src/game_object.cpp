#include "game_object.h"

#include "renderer.h"
#include "game.h"

GameObject::GameObject() {}

GameObject::GameObject(std::unique_ptr<InputComponent> input,
                       std::unique_ptr<PhysicsComponent> physics,
                       std::unique_ptr<GraphicsComponent> graphics)
{
    AddComponent(std::move(input));
    AddComponent(std::move(physics));
    AddComponent(std::move(graphics));
}

void GameObject::AddComponent(std::unique_ptr<InputComponent> comp) {
    inputComps_.emplace_back(std::move(comp));
}

void GameObject::AddComponent(std::unique_ptr<PhysicsComponent> comp) {
    physicsComps_.emplace_back(std::move(comp));
}

void GameObject::AddComponent(std::unique_ptr<GraphicsComponent> comp) {
    graphicsComps_.emplace_back(std::move(comp));
}

void GameObject::ProcessInput(const uint8_t *keyboard_state) {
    for (auto &input: inputComps_)
        input->Update(*this, keyboard_state);
}

void GameObject::UpdatePhysics(Game &game) {
    for (auto &physics: physicsComps_)
        physics->Update(*this, game);
}

void GameObject::UpdateGraphics(class Renderer &renderer) {
    for (auto &graphics: graphicsComps_)
        graphics->Update(*this, renderer);
}
