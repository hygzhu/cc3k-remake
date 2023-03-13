#ifndef GOBLIN_H
#define GOBLIN_H

#include "entity.h"

class Goblin : public Entity {
public:
    Goblin(int x, int y);
    virtual void move(int dx, int dy);
    
    void setMovement();
    virtual void printEntityType();
private:
    int m_inMovement;
};

#endif
