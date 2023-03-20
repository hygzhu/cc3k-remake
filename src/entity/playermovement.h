#ifndef PLAYERMOVEMENT_H
#define PLAYERMOVEMENT_H


#include "movement.h"

class PlayerMovement : public Movement{

public:
    PlayerMovement(std::shared_ptr<Entity>  entity,Point p, bool collidable);
    void triggerCollisionSideEffect(std::shared_ptr<Entity> other) override;
};


#endif