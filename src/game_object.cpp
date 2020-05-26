#include "game_object.h"

#include "renderer.h"
#include "game.h"
#include "controller.h"


void GameObject::ProcessInput(class Controller const &controller) {
    input_->Update(*this, controller);
}

void GameObject::UpdatePhysics() {

}

void GameObject::UpdateGraphics(class Renderer &renderer) {
    graphics_->Update(*this, renderer);
}
