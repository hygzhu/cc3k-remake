#ifndef STARTING_ROOM_H
#define STARTING_ROOM_H

#include "room.h"

class StartingRoom : public Room {
public:
  StartingRoom(Rectangle rect, std::shared_ptr<Entity> player);
  std::vector<std::shared_ptr<Entity>> getAllEntities();

private:
};

#endif