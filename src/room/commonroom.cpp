#include "commonroom.h"
#include "../entity/entityfactory.h"
#include "../utils/random.h"
#include <iostream>
#include <algorithm>

CommonRoom::CommonRoom(Rectangle rect, std::shared_ptr<Entity> player) : Room(rect, player) {
  // Generate entities in room
  const int room_size = rect.getHeight() * rect.getWidth();
  const int block_size_per_entity = 50000;
  const int min_entities = 1;
  const int max_entities = room_size / block_size_per_entity;
  const int num_enemies = Random::randomInt(min_entities, max_entities);

  const int wall_buffer = 10;

  for (int i = 0; i < num_enemies; ++i) {

    int entityType = Random::randomInt(EntityFactory::EnemyType::GOBLIN,
                                       EntityFactory::EnemyType::RAT);
    const int x = Random::randomInt(
        rect.getX() + wall_buffer, rect.getX() + rect.getWidth() - wall_buffer);
    const int y =
        Random::randomInt(rect.getY() + wall_buffer,
                          rect.getY() + rect.getHeight() - wall_buffer);

    auto realEntityType = static_cast<EntityFactory::EnemyType>(entityType);

    if(realEntityType == EntityFactory::EnemyType::GOBLIN){
      m_enemies.push_back(EntityFactory::createFollowEnemy(realEntityType, x, y, m_player, 300));
    }else{
      m_enemies.push_back(EntityFactory::createEnemy(realEntityType, x, y));
    }
  }
  // std::cout << "Enemies generated: "<<  m_enemies.size() << std::endl;
}

std::vector<std::shared_ptr<Entity>> CommonRoom::getAllEntities() {

  std::vector<std::shared_ptr<Entity>> result;
  for (auto entity : m_entities) {
    result.push_back(entity);
  }
  for (auto entity : m_enemies) {
    result.push_back(entity);
  }
  return result;
}

std::vector<std::shared_ptr<Entity>> CommonRoom::getMovingEntities() {
  // filter enemies that are dead
  m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(),
                                 [](const std::shared_ptr<Entity> &entity) {
                                   return !entity->getStatus().isAlive();
                                 }),
                  m_enemies.end());

  return m_enemies;
}

std::vector<std::shared_ptr<Entity>> CommonRoom::getNonMovingEntities() {
  return m_entities;
}