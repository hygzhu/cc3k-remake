#include "entityfactory.h"
#include <string>

std::shared_ptr<Entity> EntityFactory::createEntity(const std::string& entityType, int x, int y) {
    if (entityType == "Goblin") {
        return std::make_shared<Goblin>(x, y);
    } else if (entityType == "Environment") {
        return std::make_shared<Environment>(x, y);
    } else {
        return nullptr;
    }
}
