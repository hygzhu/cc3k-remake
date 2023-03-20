#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Enemy : public Entity {
public:
    Enemy(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite, Status stats);

    void setMovement() override;
    virtual void printEntityType() override;
    void triggerCollisionSideEffect(std::shared_ptr<Entity> other) override;
    void tryToMove(double time, std::vector<std::shared_ptr<Entity> > otherEntities) override;

private:
    int m_movement_counter = 0;
    int m_movement_period = 0;
};

#endif