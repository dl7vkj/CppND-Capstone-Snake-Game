#include "game_object.h"

#include "renderer.h"
#include "game.h"
#include "controller.h"


void GameObject::ProcessInput(const uint8_t *keyboard_state) {
    input_->Update(*this, keyboard_state);
}

void GameObject::UpdatePhysics(Game &game) {
    physics_->Update(*this, game);
}

void GameObject::UpdateGraphics(class Renderer &renderer) {
    graphics_->Update(*this, renderer);
}
