#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <cstdint>

#include "SDL.h"


class Game;
class Component;

class GameObject {
public:
    virtual ~GameObject() {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "GameObject destructor");
    }
    virtual void ProcessInput(const uint8_t *keyboard_state) = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual SDL_FPoint &GetPosition() = 0;
    virtual void SetPosition(SDL_FPoint position) = 0;
    virtual void AddComponent(Component *component) = 0;
    virtual void RemoveComponent(Component *component) = 0;
};

#endif // GAME_OBJECT_H
