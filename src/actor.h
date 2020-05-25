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

    Actor(Game *game) : GameObject(game) {}

    virtual ~Actor() {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Actor destructor");
    }

    // void ProcessInput(const uint8_t *keyboard_state) override {
    //     if (nullptr == keyboard_state)
    //         return;
    //     for (auto &comp: components_) {
    //         comp->ProcessInput(keyboard_state);
    //     }
    // }

    // void Update() override {
    //     for (auto &comp: components_) {
    //         comp->Update();
    //     }
    // }

    Side side{Side::kNeutral};
    int health{1};
    bool isAlive{true};

protected:
    // Game *game;
};

#endif // ACTOR_H
