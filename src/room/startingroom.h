#ifndef STARTING_ROOM_H
#define STARTING_ROOM_H

#include "room.h"

class StartingRoom : public Room {
public:
    StartingRoom(BoundingRectangle rect);
    std::vector<std::shared_ptr<Entity> > getAllEntities();

private:
};

#endif