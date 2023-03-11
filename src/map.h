#ifndef MAP_H
#define MAP_H

#include <vector>
#include <memory>
#include "entity.h"
#include <utility>
#include "room.h"

#include "boundingrectangle.h"
#include "corridor.h"

class Map {
public:
    Map(std::shared_ptr<Entity> player);
    ~Map();
    std::vector<std::shared_ptr<Entity> > & getEntities();
    std::vector<std::shared_ptr<Entity> > getViewboxEntities();
    int getWidth();
    int getHeight();
    bool canEntityMove(int x, int y, std::shared_ptr<Entity> entity);
    std::pair<int,int> movableLocationCloseTo(int x, int y, std::shared_ptr<Entity> entity);
    bool doesEntityCollideAt(int x, int y, std::shared_ptr<Entity> entity);
    BoundingRectangle getViewBox();

private:
    std::vector<std::shared_ptr<Entity> > entities;

    std::vector<std::shared_ptr<Room> > m_rooms;
    std::vector<std::shared_ptr<Corridor> > m_corridors;
    std::shared_ptr<Entity> player;
    int x,y;
    int width;
    int height;
    int max_width;
    int max_height;
    int randomInt(int min, int max);
    BoundingRectangle generateRectangle(BoundingRectangle bounds, std::vector<BoundingRectangle>& rectangles, int margin);
    void generateCorridors();

};

#endif
