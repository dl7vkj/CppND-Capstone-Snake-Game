#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "component.h"


class InputComponent : public Component {
public:
    virtual void Update(class GameObject &obj, const uint8_t *keyboard_state) = 0;
};


#endif // INPUT_COMPONENT_H
