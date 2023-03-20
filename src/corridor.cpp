#include "corridor.h"
#include "entity/entityfactory.h"
#include <deque>
#include <iostream>
#include <string>
#include <unordered_set>

Corridor::Corridor() {}

Corridor::Corridor(std::vector<Point> points, int size) {
  for (int i = 0; i < points.size(); i++) {
    Point curr = points[i];
    Rectangle rect(curr.getX() - size, curr.getY() - size, size * 2, size * 2);
    addFloor(rect);
  }
}

std::vector<std::shared_ptr<Entity>> &Corridor::getEntities() {
  return m_entities;
}

void Corridor::addFloor(Rectangle rect) {
  std::shared_ptr<Entity> floor = EntityFactory::createRectangularEntity(
      EntityFactory::EntityType::FLOOR, rect);
  m_entities.push_back(floor);
}