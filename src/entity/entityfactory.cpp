#include "entityfactory.h"
#include <string>

#include "environment.h"
#include "floor.h"
#include "enemy.h"


#include "../graphics/spritefactory.h"

std::shared_ptr<Entity> EntityFactory::createEntity(EntityType entitytype, int x, int y) {

    return nullptr;

}


std::shared_ptr<Entity> EntityFactory::createEnemy(EnemyType enemyType, int x, int y) {
    
    Point p(x,y);
    
    if (enemyType == EnemyType::GOBLIN ) {

        Rectangle gobRect(0,0,7,7);
        auto goblinSprite = SpriteFactory::createRectangularSprite(SpriteFactory::SpriteType::RECTANGULAR, gobRect, { 0, 128, 0, 255});
        Hitbox gobHitbox = Hitbox(gobRect, p);
        return std::make_shared<Enemy>(p, gobHitbox, goblinSprite);

    } else if (enemyType == EnemyType::RAT ) {

        Rectangle ratRect(0,0,7,5);
        std::shared_ptr<Sprite> ratSprite = SpriteFactory::createRectangularSprite(SpriteFactory::SpriteType::RECTANGULAR, ratRect, { 79, 49, 4, 255});
        Hitbox ratHitbox = Hitbox(ratRect, p);
        return std::make_shared<Enemy>(p, ratHitbox, ratSprite);

    }  else if (enemyType == EnemyType::DRAGON ) {

        Rectangle rect(0,0,50,50);
        std::shared_ptr<Sprite> sprite = SpriteFactory::createRectangularSprite(SpriteFactory::SpriteType::RECTANGULAR, rect, { 79, 49, 4, 255});
        Hitbox hitbox = Hitbox(rect, p);
        return std::make_shared<Enemy>(p, hitbox, sprite);

    }else {
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