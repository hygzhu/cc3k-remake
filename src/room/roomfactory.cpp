#include "roomfactory.h"
#include "commonroom.h"
#include "startingroom.h"

std::shared_ptr<Room> RoomFactory::createRoom(RoomType roomtype,
                                              Rectangle bounds, 
                                              std::shared_ptr<Entity> player) {

  if (roomtype == RoomType::COMMON) {
    return std::make_shared<CommonRoom>(bounds,player);
  } else if (roomtype == RoomType::UNCOMMON) {
    return nullptr;
  } else if (roomtype == RoomType::STARTING) {
    return std::make_shared<StartingRoom>(bounds, player);
  } else {
    return nullptr;
  }
}
