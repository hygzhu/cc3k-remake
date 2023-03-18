#ifndef RAT_H
#define RAT_H

#include "entity.h"

class Rat : public Entity {
public:
    Rat(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite);

    void setMovement();
    virtual void printEntityType();
private:
    int m_inMovement;
};

#endif