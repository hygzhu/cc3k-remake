#ifndef GOBLIN_H
#define GOBLIN_H

#include "entity.h"

class Goblin : public Entity {
public:
    Goblin(int x, int y);
    virtual void move(int dx, int dy);
    virtual int getX() const;
    virtual int getY() const;

private:
    int x;
    int y;
};

#endif
