#include "room.h"
#include "../entity/entityfactory.h"
#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <unordered_set>

Room::Room(Rectangle rect, std::shared_ptr<Entity> player) : m_bounds(rect), m_player(player) {
  // generate floor
  std::shared_ptr<Entity> floor = EntityFactory::createRectangularEntity(
      EntityFactory::EntityType::FLOOR, rect);
  m_entities.push_back(floor);

  // std::cout << "Entities size " << m_entities.size() << std::endl;
}

std::vector<std::shared_ptr<Entity>> &Room::getEntities() { return m_entities; }

Rectangle Room::getBounds() { return m_bounds; }

void Room::print() { m_bounds.print(); }

std::vector<std::shared_ptr<Entity>> Room::getMovingEntities() {
  std::vector<std::shared_ptr<Entity>> ret;
  return ret;
}

std::vector<std::shared_ptr<Entity>> Room::getNonMovingEntities() {

  return m_entities;
}