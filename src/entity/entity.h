#ifndef ENTITY_H
#define ENTITY_H

#include "../geometry/rectangle.h"
#include "../geometry/hitbox.h"
#include "../graphics/sprite.h"
#include "../gameplay/status.h"
#include <memory>


class Entity {
public:
    Entity(Rectangle rect, std::shared_ptr<Sprite> sprite);
    Entity(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite, Status status);
    virtual ~Entity() {}
    
    virtual void printEntityType() = 0;

    //Movement items
    virtual bool collidable();
    virtual void setMovement();
    int & getAccelX();
    int & getAccelY();
    void move(int x, int y);
    

    virtual void tryToMove(double time, std::vector<std::shared_ptr<Entity> > otherEntities);
    Point closestMovablePoint(Point p, std::vector<std::shared_ptr<Entity> > otherEntities);
    bool doesEntityCollideAt(Point p, std::vector<std::shared_ptr<Entity> > otherEntities);

    Point getPoint();
    Hitbox getHitbox();
    std::shared_ptr<Sprite> getSprite();
    Status getStatus();

    

protected:
    int m_x;
    int m_y;
    int m_accelx;
    int m_accely;
    Hitbox m_hitbox;
    std::shared_ptr<Sprite> m_sprite;
    Status m_status;

};

#endif
