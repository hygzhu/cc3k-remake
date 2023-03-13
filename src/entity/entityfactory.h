#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include <memory>
#include "entity.h"

class EntityFactory {
public:
    enum EntityType { WALL = 0, FLOOR = 1, GOBLIN = 2};
    static std::shared_ptr<Entity> createEntity(EntityType entitytype, int x, int y);

    static std::shared_ptr<Entity> createRectangularEntity(EntityType entitytype, BoundingRectangle rect);
};

#endif
