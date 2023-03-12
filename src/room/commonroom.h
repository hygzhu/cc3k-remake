#ifndef COMMON_ROOM_H
#define COMMON_ROOM_H

#include "room.h"

class CommonRoom : public Room {
public:
    CommonRoom(BoundingRectangle rect);
    
    virtual std::vector<std::shared_ptr<Entity> >& getEntities();

private:
};

#endif