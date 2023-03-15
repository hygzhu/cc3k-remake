#ifndef ROOM_FACTORY_H
#define ROOM_FACTORY_H

#include <memory>
#include "room.h"
#include "../geometry/rectangle.h"

class RoomFactory {
public:
    enum RoomType{ STARTING = 0, COMMON = 1, UNCOMMON = 2};
    static std::shared_ptr<Room> createRoom(RoomType roomType, Rectangle bounds);
};

#endif /* ROOM_FACTORY_H */
