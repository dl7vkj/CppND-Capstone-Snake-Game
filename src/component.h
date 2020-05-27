#ifndef COMPONENT_H
#define COMPONENT_H


class Component {
public:
    enum Type{kInput, kPhysics, kGraphics};

    virtual ~Component() {}
    virtual Type GetType() const = 0;
    // TODO: Add receive method
};


#endif // COMPONENT_H
