#ifndef PLAYER
#define PLAYER


#include <SDL.h>

#include "entity.h"

class Player : public Entity {
public:
    Player(int size, RGBA color);

    virtual void move(int dx, int dy);

    virtual void printEntityType();
};


#endif
