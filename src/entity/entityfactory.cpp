#include "entityfactory.h"
#include <string>

#include "goblin.h"
#include "environment.h"
#include "floor.h"
#include "rat.h"

std::shared_ptr<Entity> EntityFactory::createEntity(EntityType entitytype, int x, int y) {

    return nullptr;

}


std::shared_ptr<Entity> EntityFactory::createEnemy(EnemyType enemyType, int x, int y) {
    if (enemyType == EnemyType::GOBLIN ) {
        return std::make_shared<Goblin>(x, y);
    } else if (enemyType == EnemyType::RAT ) {
        return std::make_shared<Rat>(x, y);
    } else {
        return nullptr;
    }
}




std::shared_ptr<Entity> EntityFactory::createRectangularEntity(EntityType entitytype, Rectangle rect){

    if (entitytype == EntityType::FLOOR ) {
        return std::make_shared<Floor>(rect);
    } else {
        return nullptr;
    }
}