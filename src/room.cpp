#include "room.h"
#include <string>
#include "entityfactory.h"
#include <iostream>
#include <unordered_set>
#include <deque>
#include <algorithm>

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


void Room::generateDoors(std::vector<std::shared_ptr<Corridor>> corridors, std::vector<Point> doorCenters){

    std::cout << "Size of room entities before doors: " << m_entities.size() << std::endl;
    std::vector<std::shared_ptr<Entity>> filtered_out;

    //Remove two points on each side of door touching corridor
    auto entityTouchesCorridor = [&](std::shared_ptr<Entity> entity) { 
        for(auto corridor: corridors){
            for(std::shared_ptr<Entity> corridorEntity: corridor->getEntities()){
                if(entity->getBoundingRectangle().isCollidingWith(corridorEntity->getBoundingRectangle())){
                    return true;
                }
            }   
        }
        return false;
    };
    std::copy_if(m_entities.begin(), m_entities.end(), std::back_inserter(filtered_out), entityTouchesCorridor); //Get filtered out items

    auto newEnd = std::remove_if(m_entities.begin(), m_entities.end(), entityTouchesCorridor);
    m_entities.erase(newEnd, m_entities.end());

    // Run BFS to remove door from center spreading 
    std::cout << "Filtered out items: " << filtered_out.size() << std::endl;

    std::vector<Point> entityPoints;
    for(auto entity :filtered_out){
        entityPoints.push_back(Point(entity->getBoundingRectangle().getX(), entity->getBoundingRectangle().getY()));
    }
    for(Point doorCenter : doorCenters){
        if(m_bounds.isCollidingWith(BoundingRectangle(doorCenter.getX(), doorCenter.getY(), 1,1))){

            std::cout << "Found colliding room! " << std::endl;
            // m_bounds.print();
            // doorCenter.print();
            //BFS
            std::deque<Point> queue;
            std::unordered_set<Point, Point::HashFunction> seen;
            queue.push_back(doorCenter);
            std::cout << "RUNNING BFS :" <<std::endl;
            doorCenter.print();
            // Print out the elements in the vector
            for (const auto& point : entityPoints) {
                std::cout << "(" << point.getX() << ", " << point.getY() << ")";
            }
            std::cout <<  std::endl;


            int i = 0;
            while(queue.size()){
                i++;
                if(i == 200){
                    break;
                }
                Point curr = queue.front();
                queue.pop_front();
                seen.insert(curr);

                for(Point neighbour : curr.getCompassSurroundingPoints()){
                    bool notSeenBefore = !(seen.count(neighbour) > 0);
                    bool insideOfDoor = !(std::find(entityPoints.begin(), entityPoints.end(), neighbour) != entityPoints.end());

                    //THIS LINE IS BUGGED, doesnt make sense
                    bool inRectangle = m_bounds.getClosestPointTo(neighbour) == neighbour;

                    
                    std::cout << notSeenBefore <<insideOfDoor<<inRectangle  << std::endl;
                    neighbour.print();
                    m_bounds.getClosestPointTo(neighbour).print();

                    if(notSeenBefore && insideOfDoor && inRectangle)
                    {
                        queue.push_back(neighbour);
                        seen.insert(neighbour);
                    }
                }
            }

            std::cout << "Door tiles " << seen.size() << std::endl;
            // Delete all room entities in door points
            auto entityIsDoor = [&](std::shared_ptr<Entity> entity) { 
                return seen.count(Point(entity->getX(), entity->getY())) > 0;
            };
            auto newEnd = std::remove_if(m_entities.begin(), m_entities.end(), entityIsDoor);
            m_entities.erase(newEnd, m_entities.end());
        }
    }



    std::cout << "Size of room entities after doors: " << m_entities.size() << std::endl;
}