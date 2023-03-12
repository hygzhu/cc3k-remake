#include "entityfactory.h"
#include <string>

std::shared_ptr<Entity> EntityFactory::createEntity(EntityType entitytype, int x, int y) {
    if (entitytype == EntityType::GOBLIN ) {
        return std::make_shared<Goblin>(x, y);
    } else if (entitytype == EntityType::WALL ) {
        return std::make_shared<Environment>(x, y);
    } else {
        return nullptr;
    }
}
