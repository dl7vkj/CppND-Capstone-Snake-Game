#ifndef BULLET_GRAPHICS_COMPONENT_H
#define BULLET_GRAPHICS_COMPONENT_H

#include "graphics_component.h"


class BulletGraphicsComponent : public GraphicsComponent {
public:
    void Update(class GameObject &obj, class Renderer &renderer) override {}
};


#endif // BULLET_GRAPHICS_COMPONENT_H
