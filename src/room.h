#ifndef ROOM_H
#define ROOM_H

#include "corridor.h"
#include "boundingrectangle.h"
#include "entity.h"
#include <vector>
#include <memory>
#include "point.h"

class Corridor;

class Room{
public:
    Room(BoundingRectangle rect);
    BoundingRectangle getBounds();
    const std::vector<std::shared_ptr<Entity> >& getEntities();
    void generateDoors(std::vector<std::shared_ptr<Corridor>> corridors, std::vector<Point> doorCenters);
    void print();
private:
    BoundingRectangle m_bounds;
    std::vector<std::shared_ptr<Entity> > m_entities;

};

#endif