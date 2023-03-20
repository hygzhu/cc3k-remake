#include "enemy.h"
#include <iostream>
#include "../utils/random.h"
#include <string>
#include "player.h"

Enemy::Enemy(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite, Status stats) : 
Entity(p, hitbox, sprite, stats), m_movement_period(Random::randomInt(0, 20))  {}


void Enemy::printEntityType(){
    std::cout<<"Enemy "<< std::endl;
}
