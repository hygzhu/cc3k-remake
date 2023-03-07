#ifndef ROOM_H
#define ROOM_H

#include "boundingrectangle.h"
#include "entity.h"
#include <vector>

class Room{
public:
    Room(BoundingRectangle rect);
    BoundingRectangle getBounds();
    const std::vector<std::shared_ptr<Entity> >& getEntities();
private:
    BoundingRectangle m_bounds;
    std::vector<std::shared_ptr<Entity> > m_entities;

};

#endif