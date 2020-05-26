#ifndef PLAYER_INPUT_COMPONENT_H
#define PLAYER_INPUT_COMPONENT_H

#include "input_component.h"


class PlayerInputComponent : public InputComponent {
public:
    void Update(class GameObject &obj, class Controller &controller) override {}
};


#endif // PLAYER_INPUT_COMPONENT_H
