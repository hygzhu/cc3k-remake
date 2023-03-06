#include "map.h"

Map::Map(): width(10), height(10) {
    grid.resize(height);
    for (int y = 0; y < height; y++) {
        grid[y].resize(width);
    }
}

Map::Map(int width, int height)
    : width(width), height(height) {
    grid.resize(height);
    for (int y = 0; y < height; y++) {
        grid[y].resize(width);
    }
}

Map::~Map() {}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}


std::vector<std::vector<std::vector<std::shared_ptr<Entity> > > >& Map::getGrid()
{
    return grid;
}

void Map::setEntity(int x, int y, std::shared_ptr<Entity> entity) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        grid[y][x].push_back(entity);
    }
}