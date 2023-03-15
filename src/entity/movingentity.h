#ifndef MOVINGENTITY_H
#define MOVINGENTITY_H


#include "../geometry/point.h"
#include "entity.h"

class MovingEntity : public Entity{

public:
    MovingEntity(Point p);
    int & getAccelX(){ return m_accelx;}
    int & getAccelY(){return m_accely;}

private:
    int m_accelx;
    int m_accely;
};

#endif