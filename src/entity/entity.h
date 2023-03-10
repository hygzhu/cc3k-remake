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
    Entity(BoundingRectangle rect,RGBA color);
    virtual ~Entity() {}
    virtual void move(int x, int y) = 0;
    virtual void printEntityType() = 0;

    virtual bool collidable();
    virtual void setMovement();

    int getX() const { return m_x; }
    int getY() const { return m_y; }
    void setX(int x) { m_x = x; }
    void setY(int y) { m_y = y; }

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    void setWidth(int x) { m_width = x; }
    void setHeight(int y) { m_height = y; }
    BoundingRectangle getBoundingRectangle();


    int & getAccelX(){ return m_accelx;}
    int & getAccelY(){return m_accely;}


    int getSize() const {return m_width;}
    RGBA getColor() const { return m_color; }
protected:
    int m_x;
    int m_y;
    int m_accelx;
    int m_accely;
    int m_width;
    int m_height;
    RGBA m_color;
};

#endif
