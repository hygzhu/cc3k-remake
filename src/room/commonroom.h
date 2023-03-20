#ifndef COMMON_ROOM_H
#define COMMON_ROOM_H

#include "room.h"

class CommonRoom : public Room {
public:
  CommonRoom(Rectangle rect);

  std::vector<std::shared_ptr<Entity>> getAllEntities();

  std::vector<std::shared_ptr<Entity>> getMovingEntities();
  std::vector<std::shared_ptr<Entity>> getNonMovingEntities();

private:
  std::vector<std::shared_ptr<Entity>> m_enemies;
};

#endif