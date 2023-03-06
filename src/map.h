#ifndef MAP_H
#define MAP_H

#include <vector>
#include <memory>
#include "entity.h"

class Map {
public:
    Map();
    Map(int width, int height);
    ~Map();

    int getWidth() const;
    int getHeight() const;

    std::vector<std::vector<std::vector<std::shared_ptr<Entity> > > >& getGrid();

    void setEntity(int x, int y, std::shared_ptr<Entity> entity);

private:
    int width;
    int height;
    std::vector<std::vector<std::vector<std::shared_ptr<Entity> > > >grid;
};

#endif
