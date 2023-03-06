#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
    virtual ~Entity() {}
    virtual void move(int dx, int dy) = 0;
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual int getSize() const = 0;
};

#endif
