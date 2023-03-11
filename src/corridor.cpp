#include "corridor.h"
#include <string>
#include "entityfactory.h"

Corridor::Corridor()
{
}


std::vector<std::shared_ptr<Entity> >& Corridor::getEntities(){
    return m_entities;
}


void Corridor::addWall(Point p)
{
    std::shared_ptr<Entity> environment = EntityFactory::createEntity("Environment", p.getX(), p.getY()); 
    m_entities.push_back(environment);
}