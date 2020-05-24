#ifndef COMPONENT_H
#define COMPONENT_H

#include <cstdint>

class GameObject;

class Component {
public:
    // Component();
    virtual ~Component() {}
    virtual void Update() {};
    virtual void SetOwner(GameObject *owner) { this->owner = owner; }
    virtual void ProcessInput(const uint8_t *keyboard_state) {}
protected:
    GameObject *owner{nullptr};
};


#endif // COMPONENT_H
