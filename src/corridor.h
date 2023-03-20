#ifndef CORRIDOR_H
#define CORRIDOR_H

#include "entity/entity.h"
#include "geometry/point.h"
#include "geometry/rectangle.h"
#include "room/room.h"
#include <memory>
#include <vector>

class Room;

class Corridor {
public:
  Corridor();
  Corridor(std::vector<Point> points, int size);
  std::vector<std::shared_ptr<Entity>> &getEntities();
  void addFloor(Rectangle rect);
  void print();

private:
  std::vector<std::shared_ptr<Entity>> m_entities;
};

#endif