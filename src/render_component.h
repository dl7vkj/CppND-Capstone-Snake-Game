#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "component.h"


class RenderComponent : virtual public Component {
public:
    virtual ~RenderComponent() {}
    virtual void Draw() = 0;
};


#endif // RENDER_COMPONENT_H
