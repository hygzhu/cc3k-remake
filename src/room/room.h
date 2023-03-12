#ifndef ROOM_H
#define ROOM_H

#include "../corridor.h"
#include "../geometry/boundingrectangle.h"
#include "../entity/entity.h"
#include <vector>
#include <memory>
#include "../geometry/point.h"

class Corridor;

class Room{
public:
    Room(BoundingRectangle rect);
    BoundingRectangle getBounds();

    std::vector<std::shared_ptr<Entity> >& getEntities();

    virtual std::vector<std::shared_ptr<Entity> > getMovingEntities();

    virtual std::vector<std::shared_ptr<Entity> > getEntitiesToBeRendered() = 0;

    void generateDoors(std::vector<std::shared_ptr<Corridor>> corridors, std::vector<Point> doorCenters);
    void print();
protected:
    BoundingRectangle m_bounds;
    std::vector<std::shared_ptr<Entity> > m_entities;

};

#endif