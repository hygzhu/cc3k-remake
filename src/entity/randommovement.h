#ifndef RANDOMMOVEMENT_H
#define RANDOMMOVEMENT_H

#include "movement.h"

class RandomMovement : public Movement{

public:
    RandomMovement(std::shared_ptr<Entity>  entity,Point p, bool collidable);

    void setMovement() override;
    void tryToMove(double time, std::vector<std::shared_ptr<Entity> > otherEntities) override;
    void triggerCollisionSideEffect(std::shared_ptr<Entity> other) override;
private:
    int m_movement_counter = 0;
};

#endif