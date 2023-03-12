#include "roomfactory.h"


std::shared_ptr<Room> RoomFactory::createRoom(const std::string& roomType, BoundingRectangle bounds) {

    if (roomType == "common") {
        return nullptr;
    } else if (roomType == "rare") {
        return nullptr;
    } else {
        return nullptr;
    }
}
