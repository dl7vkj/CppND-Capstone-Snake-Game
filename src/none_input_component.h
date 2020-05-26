#ifndef NONE_INPUT_COMPONENT_H
#define NONE_INPUT_COMPONENT_H

#include "input_component.h"


class NoneInputComponent : public InputComponent {
public:
    void Update(class GameObject &obj[[maybe_unused]],
                const uint8_t *keyboard_state[[maybe_unused]]) override {}
};


#endif // NONE_INPUT_COMPONENT_H
