#include "enemy.h"
#include <iostream>
#include "../utils/random.h"
#include <string>

Enemy::Enemy(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite) : Entity(p, hitbox, sprite), m_inMovement(0)  {}


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