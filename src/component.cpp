#include "component.h"

#include "actor.h"


Component::Component(GameObject *game_object) : owner(game_object) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Adding component to owner");
    // owner->AddComponent(this);
}

Component::~Component() {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Removing component from owner");
    if (nullptr == owner) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "owner points to nullptr!");
        return;
    }
    // owner->RemoveComponent(this);
}
