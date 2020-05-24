#ifndef COMPONENT_H
#define COMPONENT_H

#include <cstdint>

class GameObject;

class Component {
public:
    // friend class Actor;
    Component(GameObject *owner);
    virtual ~Component();
    virtual void Update() {};
    virtual void ProcessInput(const uint8_t *keyboard_state) {}
protected:
    GameObject *owner;
};


#endif // COMPONENT_H
