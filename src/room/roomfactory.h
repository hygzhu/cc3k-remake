#ifndef ROOM_FACTORY_H
#define ROOM_FACTORY_H

#include <memory>
#include "room.h"
#include "../geometry/boundingrectangle.h"

class RoomFactory {
public:
    static std::shared_ptr<Room> createRoom(const std::string& roomType, BoundingRectangle bounds);
};

#endif /* ROOM_FACTORY_H */
