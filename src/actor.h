#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include <algorithm>
#include <memory>

#include "SDL.h"

#include "game_object.h"
#include "component.h"


class Actor : public GameObject {
public:
    enum Side{ kPlayer, kAlien, kNeutral};

    Actor(Game *game) : game(game) {}

    virtual ~Actor() {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Actor destructor");
        // while (!components_.empty()) {
        //     delete components_.back();
        // }
    }

    void ProcessInput(const uint8_t *keyboard_state) override {
        if (nullptr == keyboard_state)
            return;
        for (auto &comp: components_) {
            comp->ProcessInput(keyboard_state);
        }
    }

    void Update() override {
        for (auto &comp: components_) {
            comp->Update();
        }
    }

    void Draw() override {};

    Game *GetGame() override { return game; };

    SDL_FPoint &GetPosition() override { return position; }
    void SetPosition(SDL_FPoint position) override { this->position = position; }
    void SetPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }
    SDL_Point &GetSize() { return size; }

    // void AddComponent(Component *component) override {
    //     if (nullptr == component)
    //         return;
    //     components_.push_back(component);
    // }

    // void RemoveComponent(Component *component) override {
    //     if (nullptr == component)
    //         return;
    //     auto result = std::find(components_.begin(), components_.end(), component);
    //     if (result != components_.end()) {
    //         components_.erase(result);
    //         // component->owner = nullptr;
    //     }
    // }
    bool isAlive{true};
    Side side{Side::kNeutral};


protected:
    Game *game;
    SDL_FPoint position{0.0f, 0.0f};
    SDL_Point size{0, 0};
    std::vector<std::unique_ptr<Component>> components_{};
};

#endif // ACTOR_H
