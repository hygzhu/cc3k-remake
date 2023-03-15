#ifndef MAP_H
#define MAP_H

#include <vector>
#include <memory>
#include "entity/entity.h"
#include <utility>
#include "room/room.h"

#include "geometry/rectangle.h"
#include "corridor.h"

class Map {
public:
    Map(std::shared_ptr<Entity> player, int numRooms, int roomMargin, int corridorWidth);
    ~Map();
    std::vector<std::shared_ptr<Entity> > & getEntities();
    std::vector<std::shared_ptr<Entity> > getViewboxStaticEntities();
    std::vector<std::shared_ptr<Entity> > getViewboxMovingEntities();
    std::vector<std::shared_ptr<Entity> > getMovingEntities();
    std::vector<std::shared_ptr<Entity> > getAllEntities();
    int getWidth();
    int getHeight();
    bool canEntityMove(int x, int y, std::shared_ptr<Entity> entity);
    std::pair<int,int> movableLocationCloseTo(int x, int y, std::shared_ptr<Entity> entity);
    bool doesEntityCollideAt(int x, int y, std::shared_ptr<Entity> entity);
    Rectangle getViewBox();

    void updateAllMovableEntityLocations(double time);

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
    Rectangle generateRectangle(Rectangle bounds, std::vector<Rectangle>& rectangles, int margin);
    void generateCorridors(int corridorWidth);

};

#endif
