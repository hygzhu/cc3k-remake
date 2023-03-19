#include "enemy.h"
#include <iostream>
#include "../utils/random.h"
#include <string>
#include "player.h"

Enemy::Enemy(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite, Status stats) : Entity(p, hitbox, sprite, stats), m_inMovement(0)  {}


void Enemy::printEntityType(){
    std::cout<<"Enemy " << m_x << " " << m_y << std::endl;
}


void Enemy::setMovement(){

    if(!m_inMovement){
        int base_acceleration = 100;
        int rand = Random::randomInt(0,1);
        if(rand == 0){
            rand = -1;
        }
        m_accelx = base_acceleration*rand;
        rand = Random::randomInt(0,1);
        if(rand == 0){
            rand = -1;
        }
        m_accely = base_acceleration*rand;

        m_inMovement = 60;
    }else{
        m_inMovement -=1;
    }

}


void Enemy::triggerCollisionSideEffect(std::shared_ptr<Entity> other){

    auto player = std::dynamic_pointer_cast<Player>(other);
    if(player != nullptr){
        if(!other->isInvincible()){
            other->getStatus().defendFrom(m_status);
            other->setInvincible(true);
        }

    }


}