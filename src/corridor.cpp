#include "corridor.h"
#include <string>
#include "entity/entityfactory.h"
#include <deque>
#include <unordered_set>
#include <iostream>

Corridor::Corridor()
{
}

Corridor::Corridor(std::vector<Point> points, int size)
{
    for(int i = 0; i < points.size(); i++){
        Point curr = points[i];
        BoundingRectangle rect(curr.getX()-size, curr.getY()-size, size*2, size*2);
        addFloor(rect);
    }
}

std::vector<std::shared_ptr<Entity> >& Corridor::getEntities(){
    return m_entities;
}

void Corridor::addFloor(BoundingRectangle rect){
    std::shared_ptr<Entity> floor = EntityFactory::createRectangularEntity(EntityFactory::EntityType::FLOOR, rect); 
    m_entities.push_back(floor);
}

void Corridor::removeEntitiesInRooms(std::vector<std::shared_ptr<Room>> rooms)
{
    //std::vector<std::shared_ptr<Entity>> filtered_out;

    auto isInRoom = [&](std::shared_ptr<Entity> entity) { 
        for(std::shared_ptr<Room> room : rooms){
            if(room->getBounds().isCollidingWith(entity->getBoundingRectangle())){
                return true;
            }
        }
        return false;
    };

    //std::remove_copy_if(m_entities.begin(), m_entities.end(), std::back_inserter(filtered_out), isInRoom);

    auto newEnd = std::remove_if(m_entities.begin(), m_entities.end(), isInRoom);
    m_entities.erase(newEnd, m_entities.end());

    //return filtered_out;
}