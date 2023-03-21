#include "startingroom.h"

StartingRoom::StartingRoom(Rectangle rect, std::shared_ptr<Entity> player) : Room(rect, player) {
  // Generate entities in room
}

std::vector<std::shared_ptr<Entity>> StartingRoom::getAllEntities() {
  return m_entities;
}
