#ifndef MAP_H
#define MAP_H

#include "entity/entity.h"
#include "room/room.h"
#include <memory>
#include <utility>
#include <vector>

#include "corridor.h"
#include "geometry/rectangle.h"

class Map {
public:
  Map(std::shared_ptr<Entity> player, int numRooms, int roomMargin,
      int corridorWidth);
  ~Map();
  std::vector<std::shared_ptr<Entity>> &getEntities();
  std::vector<std::shared_ptr<Entity>> getViewboxStaticEntities();
  std::vector<std::shared_ptr<Entity>> getViewboxMovingEntities();
  std::vector<std::shared_ptr<Entity>> getMovingEntities();
  std::vector<std::shared_ptr<Entity>> getAllEntities();

  int getWidth();
  int getHeight();
  Rectangle getViewBox();
  std::shared_ptr<Entity> getPlayer() { return player; }

  void updateAllMovableEntityLocations(double time);

private:
  std::vector<std::shared_ptr<Entity>> entities;
  std::vector<std::shared_ptr<Room>> m_rooms;
  std::vector<std::shared_ptr<Corridor>> m_corridors;
  std::shared_ptr<Entity> player;
  int x, y;
  int width;
  int height;
  int max_width;
  int max_height;
  int randomInt(int min, int max);
  Rectangle generateRectangle(Rectangle bounds,
                              std::vector<Rectangle> &rectangles, int margin);
  void generateCorridors(int corridorWidth);
};

#endif
