#ifndef RAT_H
#define RAT_H

#include "entity.h"

class Rat : public Entity {
public:
    Rat(int x, int y);
    virtual void move(int dx, int dy);

    void setMovement();
    virtual void printEntityType();
private:
    int m_inMovement;
};

#endif