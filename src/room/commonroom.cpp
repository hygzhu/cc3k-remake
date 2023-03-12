#include "commonroom.h"
#include "../entity/entityfactory.h"

CommonRoom::CommonRoom(BoundingRectangle rect): Room(rect){
    // Generate entities in room
}


std::vector<std::shared_ptr<Entity> >& CommonRoom::getEntities(){
    return m_entities;
}
