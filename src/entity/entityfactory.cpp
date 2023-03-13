#include "entityfactory.h"
#include <string>

#include "goblin.h"
#include "environment.h"
#include "floor.h"

std::shared_ptr<Entity> EntityFactory::createEntity(EntityType entitytype, int x, int y) {
    if (entitytype == EntityType::GOBLIN ) {
        return std::make_shared<Goblin>(x, y);
    } else if (entitytype == EntityType::WALL ) {
        return std::make_shared<Environment>(x, y);
    } else {
        return nullptr;
    }
}



std::shared_ptr<Entity> EntityFactory::createRectangularEntity(EntityType entitytype, BoundingRectangle rect){

    if (entitytype == EntityType::FLOOR ) {
        return std::make_shared<Floor>(rect);
    } else {
        return nullptr;
    }
}