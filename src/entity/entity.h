#ifndef ENTITY_H
#define ENTITY_H

#include "../geometry/rectangle.h"
#include "../geometry/hitbox.h"
#include "../graphics/sprite.h"
#include <memory>


class Entity {
public:
    Entity(Rectangle rect, std::shared_ptr<Sprite> sprite);
    Entity(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite);
    virtual ~Entity() {}
    
    void move(int x, int y);
    virtual void printEntityType() = 0;
    virtual bool collidable();
    virtual void setMovement();

    int & getAccelX();
    int & getAccelY();
    Point getPoint();
    Hitbox getHitbox();
    std::shared_ptr<Sprite> getSprite();
protected:
    int m_x;
    int m_y;
    int m_accelx;
    int m_accely;
    Hitbox m_hitbox;
    std::shared_ptr<Sprite> m_sprite;
};

#endif
