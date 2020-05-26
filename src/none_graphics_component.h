#ifndef NONE_GRAPHICS_COMPONENT_H
#define NONE_GRAPHICS_COMPONENT_H

#include "graphics_component.h"


class NoneGraphicsComponent : public GraphicsComponent {
public:
    void Update(class GameObject &obj[[maybe_unused]],
                class Renderer &renderer[[maybe_unused]]) override {}
};


#endif // NONE_GRAPHICS_COMPONENT_H
