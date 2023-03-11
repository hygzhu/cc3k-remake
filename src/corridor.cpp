#include "corridor.h"
#include <string>
#include "entityfactory.h"
#include <deque>
#include <unordered_set>
#include <iostream>

Corridor::Corridor()
{
}

Corridor::Corridor(std::vector<Point> points, int size)
{
    // BFS to expand path size
    std::unordered_set<std::string> seen;
    std::deque<Point> mqueue;
    for(Point p : points){
        mqueue.push_back(p);
        seen.insert(p.toString());
    }
    std::cout << "Size of corridor before expansion " << points.size() << std::endl; 
    for(int i =0; i< size; i++){
        int curr_size = mqueue.size();
        for(int j = 0; j < curr_size; ++j){
            Point curr = mqueue.front();
            mqueue.pop_front();
            for(Point neighbour : curr.getSurroundingPoints()){
                auto it = seen.find(neighbour.toString());
                if (it == seen.end()) {
                    //std::cout << "Element not found in the set: " << *it << std::endl;
                    mqueue.push_back(neighbour);
                    seen.insert(neighbour.toString());
                } 
            }
        }
    }

    std::vector<Point> vec;
    while (!mqueue.empty()) {
        vec.push_back(mqueue.front());
        mqueue.pop_front();
    }

    std::cout << "Size of corridor after expansion " << vec.size() << std::endl; 



    for(Point p : vec){
        addWall(p);
    }
}

std::vector<std::shared_ptr<Entity> >& Corridor::getEntities(){
    return m_entities;
}


void Corridor::addWall(Point p)
{
    std::shared_ptr<Entity> environment = EntityFactory::createEntity("Environment", p.getX(), p.getY()); 
    m_entities.push_back(environment);
}