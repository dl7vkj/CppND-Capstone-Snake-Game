#ifndef STAR_GRAPHICS_COMPONENT_H
#define STAR_GRAPHICS_COMPONENT_H

#include "SDL.h"

#include "graphics_component.h"
#include "star_physics_component.h"


class StarGraphicsComponent : public GraphicsComponent {
public:
    StarGraphicsComponent(StarPhysicsComponent *starPhyC_) : starPhyC_(starPhyC_) {}

    void Update(class GameObject &obj, class Renderer &renderer) override {
        std::vector<StarPhysicsComponent::Star> const &stars = starPhyC_->GetStars();
        // TODO: Add to constructor
        SDL_Renderer *sdl_renderer = renderer.GetSDLRendererHandle();
        if (sdl_renderer == nullptr)
            return;
        for (auto &star: stars) {
            int c = star.dx;
            c *= -84;
            SDL_SetRenderDrawColor(sdl_renderer, c, c, c, 255);
            int x = star.x;
            int y = star.y;
            SDL_RenderDrawLine(sdl_renderer, x, y, x + 3, y);
        }
    }

private:
    StarPhysicsComponent *starPhyC_;
};

#endif // STAR_GRAPHICS_COMPONENT_H
