#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H

#include "component.h"


class GraphicsComponent : public Component {
public:
    virtual void Update(class GameObject &obj, class Renderer &renderer) = 0;
};


#endif // GRAPHICS_COMPONENT_H
