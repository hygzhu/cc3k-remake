#ifndef RAT_H
#define RAT_H

#include "entity.h"

class Rat : public Entity {
public:
    Rat(int x, int y);

    void setMovement();
    virtual void printEntityType();
private:
    int m_inMovement;
};

#endif