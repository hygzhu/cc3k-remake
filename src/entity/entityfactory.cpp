#include "entityfactory.h"
#include <string>

#include "enemy.h"
#include "floor.h"
#include "player.h"

#include "../graphics/spritefactory.h"

#include "movement.h"
#include "playermovement.h"
#include "randommovement.h"

std::shared_ptr<Entity> EntityFactory::createEntity(EntityType entitytype,
                                                    int x, int y) {

  return nullptr;
}

std::shared_ptr<Entity> EntityFactory::createEnemy(EnemyType enemyType, int x,
                                                   int y) {

  Point p(x, y);

  if (enemyType == EnemyType::GOBLIN) {

    Rectangle gobRect(0, 0, 7, 7);
    auto goblinSprite = SpriteFactory::createRectangularSprite(
        SpriteFactory::SpriteType::RECTANGULAR, gobRect, {0, 128, 0, 255});
    Hitbox gobHitbox = Hitbox(gobRect, p);
    Status stats(50, 0, 10, 10, 0, 0, 0, 0, 50, 0);
    std::shared_ptr<Entity> entity =
        std::make_shared<Enemy>(p, gobHitbox, goblinSprite, stats);
    std::shared_ptr<Movement> movement =
        std::make_shared<RandomMovement>(entity, p, false);
    entity->setMovement(movement);
    return entity;

  } else if (enemyType == EnemyType::RAT) {

    Rectangle ratRect(0, 0, 7, 5);
    std::shared_ptr<Sprite> ratSprite = SpriteFactory::createRectangularSprite(
        SpriteFactory::SpriteType::RECTANGULAR, ratRect, {79, 49, 4, 255});
    Hitbox ratHitbox(ratRect, p);
    Status stats(20, 0, 5, 5, 0, 0, 0, 0, 20, 0);
    std::shared_ptr<Entity> entity =
        std::make_shared<Enemy>(p, ratHitbox, ratSprite, stats);
    std::shared_ptr<Movement> movement =
        std::make_shared<RandomMovement>(entity, p, false);
    entity->setMovement(movement);
    return entity;

  } else if (enemyType == EnemyType::DRAGON) {

    Rectangle rect(0, 0, 50, 50);
    std::shared_ptr<Sprite> sprite = SpriteFactory::createRectangularSprite(
        SpriteFactory::SpriteType::RECTANGULAR, rect, {225, 20, 60, 255});
    Hitbox hitbox(rect, p);
    Status stats(500, 0, 40, 40, 0, 0, 0, 0, 500, 0);
    std::shared_ptr<Entity> entity =
        std::make_shared<Enemy>(p, hitbox, sprite, stats);
    std::shared_ptr<Movement> movement =
        std::make_shared<RandomMovement>(entity, p, false);
    entity->setMovement(movement);
    return entity;

  } else {
    return nullptr;
  }
}

std::shared_ptr<Entity> EntityFactory::createPlayer() {

  Point p(0, 0);
  Rectangle rect(0, 0, 10, 10);
  std::shared_ptr<Sprite> sprite = SpriteFactory::createRectangularSprite(
      SpriteFactory::SpriteType::RECTANGULAR, rect, {220, 220, 220, 255});
  Hitbox hitbox(rect, p);
  Status stats(100, 20, 20, 20, 0, 0, 0, 0, 100, 20);

  std::shared_ptr<Entity> entity =
      std::make_shared<Player>(p, hitbox, sprite, stats);
    
  std::shared_ptr<Movement> movement =
      std::make_shared<PlayerMovement>(entity, p, false);
  entity->setMovement(movement);
  return entity;
}

std::shared_ptr<Entity>
EntityFactory::createRectangularEntity(EntityType entitytype, Rectangle rect) {

  if (entitytype == EntityType::FLOOR) {
    
    Point p(rect.getCoordinates());
    rect.setX(0);
    rect.setY(0);

    auto sprite = SpriteFactory::createRectangularSprite(
        SpriteFactory::SpriteType::RECTANGULAR, rect, {128, 128, 128, 255});
    Hitbox floorHitbox = Hitbox(rect, p);
    Status stats;
    std::shared_ptr<Entity> entity =
        std::make_shared<Enemy>(p, floorHitbox, sprite, stats);
    std::shared_ptr<Movement> movement =
        std::make_shared<RandomMovement>(entity, p, true);
    entity->setMovement(movement);
    return entity;
  } else {
    return nullptr;
  }
}