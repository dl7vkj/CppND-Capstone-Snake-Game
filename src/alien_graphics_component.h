#ifndef ALIEN_GRAPHICS_COMPONENT_H
#define ALIEN_GRAPHICS_COMPONENT_H

#include "graphics_component.h"


class AlienGraphicsComponent : public GraphicsComponent {
public:
    void Update(class GameObject &obj, class Renderer &renderer) override {}
};


#endif // ALIEN_GRAPHICS_COMPONENT_H
