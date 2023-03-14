#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include <memory>
#include "entity.h"

class EntityFactory {
public:
    enum EntityType { 
        FLOOR = 1
    };
    enum EnemyType {
        GOBLIN = 101, 
        RAT = 102
    };

    static std::shared_ptr<Entity> createEntity(EntityType entitytype, int x, int y);

    static std::shared_ptr<Entity> createRectangularEntity(EntityType entitytype, BoundingRectangle rect);


    static std::shared_ptr<Entity> createEnemy(EnemyType enemyType, int x, int y);
};

#endif
