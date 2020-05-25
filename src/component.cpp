#include "component.h"

#include "actor.h"


Component::Component(GameObject *game_object) : owner(game_object) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Component constructor");
    // owner->AddComponent(this);
}

Component::~Component() {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Component destructor");
    if (nullptr == owner) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "owner points to nullptr!");
        return;
    }
    // owner->RemoveComponent(this);
}
