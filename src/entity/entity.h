#ifndef ENTITY_H
#define ENTITY_H

#include "../geometry/rectangle.h"
#include "../geometry/hitbox.h"

struct RGBA {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
};

class Entity {
public:
    Entity(int x, int y, int size,RGBA color);
    Entity(Rectangle rect,RGBA color);
    virtual ~Entity() {}
    void move(int x, int y);
    virtual void printEntityType() = 0;

    virtual bool collidable();
    virtual void setMovement();

    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);

    int & getAccelX();
    int & getAccelY();
    Rectangle getRectangle();

    int getSize() const {return m_width;}
    RGBA getColor() const { return m_color; }

    Hitbox getHitbox();
protected:
    int m_x;
    int m_y;
    int m_accelx;
    int m_accely;
    int m_width;
    int m_height;
    RGBA m_color;
    Hitbox m_hitbox;
};

#endif
