#ifndef COMPONENT_H
#define COMPONENT_H

#include <cstdint>

// RUBRIC: Classes follow an appropriate inheritance hierarchy.

class Component {
public:
    enum Type{kInput, kPhysics, kGraphics};

    virtual ~Component() {}
    virtual Type GetType() const = 0;
    // TODO: Add receive method
};

// RUBRIC: Derived class functions override virtual base class functions.
class InputComponent : public Component {
public:
    Type GetType() const final { return Component::Type::kInput; }

    virtual void Update(class GameObject &obj, const uint8_t *keyboard_state) = 0;
};

class PhysicsComponent : public Component {
public:
    Type GetType() const final { return Component::Type::kPhysics; }
    // RUBRIC: The project makes use of references in function declarations.
    virtual void Update(class GameObject &obj, class Game &game) = 0;
};

class GraphicsComponent : public Component {
public:
    Type GetType() const final { return Component::Type::kGraphics; }

    virtual void Update(class GameObject &obj, class Renderer &renderer) = 0;
};


#endif // COMPONENT_H
