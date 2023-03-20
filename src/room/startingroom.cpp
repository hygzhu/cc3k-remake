#include "startingroom.h"

StartingRoom::StartingRoom(Rectangle rect) : Room(rect) {
  // Generate entities in room
}

std::vector<std::shared_ptr<Entity>> StartingRoom::getAllEntities() {
  return m_entities;
}
