#ifndef ALIEN_INPUT_COMPONENT_H
#define ALIEN_INPUT_COMPONENT_H

#include "input_component.h"


class AlienInputComponent : public InputComponent {
public:
    void Update(class GameObject &obj, class Controller const &controller) override {}
};


#endif // ALIEN_INPUT_COMPONENT_H
