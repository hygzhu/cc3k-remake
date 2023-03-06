#ifndef ENTITY_H
#define ENTITY_H

#include "boundingrectangle.h"

struct RGBA {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
};

class Entity {
public:
    Entity(int x, int y, int size,RGBA color);
    virtual ~Entity() {}
    virtual void move(int x, int y) = 0;
    virtual void printEntityType() = 0;
    int getX() const { return x_; }
    int getY() const { return y_; }
    void setX(int x) { x_ = x; }
    void setY(int y) { y_ = y; }
    BoundingRectangle getBoundingRectangle();

    int getSize() const {return size_;}
    RGBA getColor() const { return color_; }
protected:
    int x_;
    int y_;
    int size_;
    RGBA color_;
};

#endif
