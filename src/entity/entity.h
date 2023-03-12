#ifndef ENTITY_H
#define ENTITY_H

#include "../geometry/boundingrectangle.h"

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
    virtual void setMovement();
    int getX() const { return x_; }
    int getY() const { return y_; }
    void setX(int x) { x_ = x; }
    void setY(int y) { y_ = y; }
    BoundingRectangle getBoundingRectangle();


    int & getAccelX(){ return m_accelx;}
    int & getAccelY(){return m_accely;}


    int getSize() const {return size_;}
    RGBA getColor() const { return color_; }
protected:
    int x_;
    int y_;
    int m_accelx;
    int m_accely;
    int size_;
    RGBA color_;
};

#endif
