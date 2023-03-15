#ifndef ROOM_H
#define ROOM_H

#include "../corridor.h"
#include "../geometry/rectangle.h"
#include "../entity/entity.h"
#include <vector>
#include <memory>
#include "../geometry/point.h"

class Corridor;

class Room{
public:
    Room(Rectangle rect);
    Rectangle getBounds();

    virtual std::vector<std::shared_ptr<Entity> >& getEntities();

    virtual std::vector<std::shared_ptr<Entity> > getMovingEntities();
    virtual std::vector<std::shared_ptr<Entity> > getNonMovingEntities();

    virtual std::vector<std::shared_ptr<Entity> > getAllEntities() = 0;

    void print();
protected:
    Rectangle m_bounds;
    std::vector<std::shared_ptr<Entity> > m_entities;

};

#endif