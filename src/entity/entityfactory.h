#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include <memory>
#include "entity.h"
#include "goblin.h"
#include "environment.h"

class EntityFactory {
public:
    static std::shared_ptr<Entity> createEntity(const std::string& entityType, int x, int y);
};

#endif
