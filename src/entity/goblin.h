#ifndef GOBLIN_H
#define GOBLIN_H

#include "entity.h"

class Goblin : public Entity {
public:
    Goblin(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite);
    
    void setMovement();
    virtual void printEntityType();
private:
    int m_inMovement;
    int m_restPoint;
};

#endif
