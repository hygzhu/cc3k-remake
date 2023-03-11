#ifndef CORRIDOR_H
#define CORRIDOR_H

#include "entity.h"
#include <vector>
#include <memory>
#include "point.h"

class Corridor {
public:
    Corridor();
    Corridor(std::vector<Point> points, int size);
    std::vector<std::shared_ptr<Entity>>& getEntities();
    void addWall(Point p);
    void print();
private:
    std::vector<std::shared_ptr<Entity>> m_entities;
};

#endif