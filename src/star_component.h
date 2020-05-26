#ifndef STAR_COMPONENT_H
#define STAR_COMPONENT_H

#include "SDL.h"

#include "render_component.h"
#include "game_object.h"
#include "star.h"


class StarComponent : public RenderComponent {
public:
    StarComponent(GameObject *owner);
    ~StarComponent();
    void Draw() override {
        Star* star = static_cast<Star*>(owner);
        int c = star->GetSpeed();
        c *= -84;
        SDL_SetRenderDrawColor(sdl_renderer, c, c, c, 255);
        SDL_FPoint pos{star->GetPosition()};
        int x = pos.x;
        int y = pos.y;
        SDL_RenderDrawLine(sdl_renderer, x, y, x + 3, y);
    }
private:
    SDL_Renderer *sdl_renderer;
};


#endif // STAR_COMPONENT_H
