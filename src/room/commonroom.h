#ifndef COMMON_ROOM_H
#define COMMON_ROOM_H

#include "room.h"

class CommonRoom : public Room {
public:
    CommonRoom(BoundingRectangle rect);
    
    std::vector<std::shared_ptr<Entity> > getEntitiesToBeRendered();

    std::vector<std::shared_ptr<Entity> > getMovingEntities();

private:
    std::vector<std::shared_ptr<Entity> > m_enemies;
};

#endif