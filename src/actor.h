#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include <algorithm>

#include "SDL.h"

#include "game_object.h"
#include "component.h"


class Actor : public GameObject {
public:
    Actor(Game &game) : game_(game) {}
    virtual ~Actor() {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Actor destructor");
    }
    void ProcessInput(const uint8_t &keyboard_state) override {
        for (auto comp: components_) {
            comp->ProcessInput(keyboard_state);
        }
    }
    void Update() override {
        for (auto comp: components_) {
            comp->Update();
        }
    }
    void Draw() override {};
    SDL_FPoint &GetPosition() override { return position_; }
    void SetPosition(SDL_FPoint &position) override { position_ = position; }
    void AddComponent(Component *component) override {
        components_.push_back(component);
    }
    void RemoveComponent(Component *component) override {
        auto result = std::find(components_.begin(), components_.end(), component);
        if (result != components_.end()) {
            components_.erase(result);
        }
    }

protected:
    Game &game_;
    SDL_FPoint position_{0.0f, 0.0f};
    std::vector<Component*> components_{};
};

#endif // ACTOR_H
