#ifndef PLAYER_GRAPHICS_COMPONENT_H
#define PLAYER_GRAPHICS_COMPONENT_H

#include "graphics_component.h"


class PlayerGraphicsComponent : public GraphicsComponent {
public:
    void Update(class GameObject &obj, class Renderer &renderer) override {}
};


#endif // PLAYER_GRAPHICS_COMPONENT_H
