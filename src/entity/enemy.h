#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Enemy : public Entity {
public:
    Enemy(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite, Status stats);

    void setMovement() override;
    virtual void printEntityType() override;

    void triggerCollisionSideEffect(std::shared_ptr<Entity> other) override;
private:
    int m_inMovement;
};

#endif