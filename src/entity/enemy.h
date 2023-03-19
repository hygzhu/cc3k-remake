#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Enemy : public Entity {
public:
    Enemy(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite);

    void setMovement();
    virtual void printEntityType();
private:
    int m_inMovement;
};

#endif