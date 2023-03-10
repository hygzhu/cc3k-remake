#ifndef CORRIDOR_H
#define CORRIDOR_H

#include "room/room.h"
#include "entity/entity.h"
#include <vector>
#include <memory>
#include "geometry/point.h"

class Room;

class Corridor {
public:
    Corridor();
    Corridor(std::vector<Point> points, int size);
    std::vector<std::shared_ptr<Entity>>& getEntities();
    void removeEntitiesInRooms(std::vector<std::shared_ptr<Room>> rooms);
    void addWall(Point p);
    void print();
private:
    std::vector<std::shared_ptr<Entity>> m_entities;
};

#endif