#ifndef PLAYER
#define PLAYER


#include <SDL.h>

#include "entity.h"

class Player : public Entity {
public:
    Player(int x, int y, int size);

    virtual void move(int dx, int dy);
    virtual int getX() const;
    virtual int getY() const;
    virtual int getSize() const;

private:
    int x;
    int y;
    int size;
};


#endif
