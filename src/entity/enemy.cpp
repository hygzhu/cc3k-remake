#include "enemy.h"
#include "../utils/random.h"
#include "player.h"
#include <iostream>
#include <string>

Enemy::Enemy(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite,
             Status stats)
    : Entity(p, hitbox, sprite, stats),
      m_movement_period(Random::randomInt(0, 20)) {}

void Enemy::printEntityType() { // std::cout << "Enemy " << std::endl;
 }
