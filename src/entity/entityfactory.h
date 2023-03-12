#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include <memory>
#include "entity.h"
#include "goblin.h"
#include "environment.h"

class EntityFactory {
public:
    enum EntityType { WALL = 0, GOBLIN = 1};
    static std::shared_ptr<Entity> createEntity(EntityType entitytype, int x, int y);
};

#endif
