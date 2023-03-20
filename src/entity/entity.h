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
    double & getAccelX();
    double & getAccelY();
    void move(double x, double y);
    virtual void tryToMove(double time, std::vector<std::shared_ptr<Entity> > otherEntities);
    Point closestMovablePoint(Point p, std::vector<std::shared_ptr<Entity> > otherEntities);
    bool isThereCollisionAtDestinationPoint(Point p, std::vector<std::shared_ptr<Entity> > otherEntities);
    virtual void triggerCollisionSideEffect(std::shared_ptr<Entity> other);
    void setInvincible(bool i);
    bool isInvincible(){return m_isInvincible;}

    Point getPoint();
    Hitbox getHitbox();
    std::shared_ptr<Sprite> getSprite();
    Status& getStatus();
    void tick(double time);
protected:
    bool m_isInvincible = false; //determines if we can trigger collision side effect

    double m_time;
    int m_tick_count = 0;

    double m_x;
    double m_y;
    double m_accelx;
    double m_accely;
    Hitbox m_hitbox;
    std::shared_ptr<Sprite> m_sprite;
    Status m_status;

};

#endif
