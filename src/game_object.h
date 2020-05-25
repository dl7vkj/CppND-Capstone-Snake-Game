#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <cstdint>
#include <vector>
#include <memory>

#include "SDL.h"

#include "component.h"

class Game;
// class Component;

class GameObject {
public:
    GameObject(Game *game) : game(game) {}
    virtual ~GameObject() {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "GameObject destructor");
    }
    virtual void ProcessInput(const uint8_t *keyboard_state) {
        if (nullptr == keyboard_state)
            return;
        for (auto &comp: components_) {
            comp->ProcessInput(keyboard_state);
        }
    }
    virtual void Update() {
        for (auto &comp: components_) {
            comp->Update();
        }
    };
    virtual void Draw() {};
    virtual SDL_FPoint GetPosition() { return position; };
    virtual void SetPosition(SDL_FPoint position) { this->position = position; }
    virtual void SetPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }
    virtual Game *GetGame() { return game; };
    virtual SDL_Rect GetRect() {
        return {
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            size.x,
            size.y
        };
    }
    virtual SDL_Point GetSize() { return size; }
    virtual void SetSize(SDL_Point size) { this->size = size; }

protected:
    Game *game;
    SDL_FPoint position{0.0f, 0.0f};
    SDL_Point size{0, 0};
    std::vector<std::unique_ptr<Component>> components_{};
};

#endif // GAME_OBJECT_H
