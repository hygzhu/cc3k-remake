#ifndef ROOM_FACTORY_H
#define ROOM_FACTORY_H

#include "../geometry/rectangle.h"
#include "room.h"
#include <memory>

class RoomFactory {
public:
  enum RoomType { STARTING = 0, COMMON = 1, UNCOMMON = 2 };
  static std::shared_ptr<Room> createRoom(RoomType roomType, Rectangle bounds,std::shared_ptr<Entity> player);
};

#endif /* ROOM_FACTORY_H */
