#ifndef PLAYER
#define PLAYER


#include "entity.h"

#include "../graphics/spritefactory.h"

class Player : public Entity {
public:
    Player(int size, RGBA color);


    virtual void printEntityType();
};


#endif
