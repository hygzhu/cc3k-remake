#include "startingroom.h"

StartingRoom::StartingRoom(BoundingRectangle rect): Room(rect){
    // Generate entities in room
}


std::vector<std::shared_ptr<Entity> > StartingRoom::getEntitiesToBeRendered(){
    return m_entities;
}
