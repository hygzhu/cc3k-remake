#include "roomfactory.h"
#include "commonroom.h"

std::shared_ptr<Room> RoomFactory::createRoom(RoomType roomtype, BoundingRectangle bounds) {

    if (roomtype == RoomType::COMMON) {
        return std::make_shared<CommonRoom>(bounds);
    } else if (roomtype == RoomType::UNCOMMON) {
        return nullptr;
    } else {
        return nullptr;
    }
}
