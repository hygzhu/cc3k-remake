#include "startingroom.h"

StartingRoom::StartingRoom(BoundingRectangle rect): Room(rect){
    // Generate entities in room
}


std::vector<std::shared_ptr<Entity> >& StartingRoom::getEntities(){
    return m_entities;
}
