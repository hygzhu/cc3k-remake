#include "room.h"
#include <string>
#include "entityfactory.h"

Room::Room(BoundingRectangle rect) :m_bounds(rect)
{
    //generate border for rectangle
    for(int i = 0; i< rect.getWidth(); i++)
    {
        for(int j = 0; j< rect.getHeight(); j++)
        {
            if (i == 0 || j == 0 || i == rect.getWidth() -1 || j == rect.getHeight() -1)
            {   
                std::shared_ptr<Entity> environment = EntityFactory::createEntity("Environment", rect.getX()+i, rect.getY()+j); 
                m_entities.push_back(environment);
            }
        }
    }
}


BoundingRectangle Room::getBounds()
{
    return m_bounds;
}


const std::vector<std::shared_ptr<Entity> >& Room::getEntities(){
    return m_entities;
}

void Room::print(){
    m_bounds.print();
}