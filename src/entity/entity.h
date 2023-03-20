#ifndef ENTITY_H
#define ENTITY_H

#include "../geometry/rectangle.h"
#include "../geometry/hitbox.h"
#include "../graphics/sprite.h"
#include "../gameplay/status.h"
#include "movement.h"
#include <memory>



class Entity {
public:
    Entity(Rectangle rect, std::shared_ptr<Sprite> sprite);
    Entity(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite, Status status);
    virtual ~Entity() {}
    
    virtual void printEntityType() = 0;

    Point getPoint();
    Hitbox& getHitbox();
    std::shared_ptr<Sprite> getSprite();
    Status& getStatus();

    void setMovement(std::shared_ptr<Movement> movement){m_movement = movement;}
    std::shared_ptr<Movement> getMovement();
    void move(double x, double y);

protected:
    std::shared_ptr<Movement> m_movement;
    Hitbox m_hitbox;
    std::shared_ptr<Sprite> m_sprite;
    Status m_status;

};

#endif
