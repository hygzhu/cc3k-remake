#include "enemy.h"
#include <iostream>
#include "../utils/random.h"
#include <string>
#include "player.h"

Enemy::Enemy(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite, Status stats) : 
Entity(p, hitbox, sprite, stats), m_movement_period(Random::randomInt(0, 20))  {}


void Enemy::printEntityType(){
    std::cout<<"Enemy " << m_x << " " << m_y << std::endl;
}


void Enemy::setMovement(){

    //std::cout << m_movement_counter << std::endl;

    if(m_movement_counter == 0){
        int base_acceleration = 80;
        // random direction
        int rand = Random::randomInt(0,2);
        if(rand == 2){
            rand = -1;
        }
        m_accelx = base_acceleration*rand;
        rand = Random::randomInt(0,2);
        if(rand == 2){
            rand = -1;
        }
        m_accely = base_acceleration*rand;
    }
    // else if (m_movement_counter + m_movement_period  % movement_end == 0){
    //     m_accelx = 0;
    //     m_accely = 0;
    // }
}


void Enemy::triggerCollisionSideEffect(std::shared_ptr<Entity> other){

    auto player = std::dynamic_pointer_cast<Player>(other);
    if(player != nullptr){
        if(!other->isInvincible()){
            other->getStatus().defendFrom(m_status);
            other->setInvincible(true);
        }
        if(!m_isInvincible){
            m_status.defendFrom(other->getStatus());
            m_isInvincible = true;
        }

    }


}

void Enemy::tryToMove(double time, std::vector<std::shared_ptr<Entity> > otherEntities){
    tick(time);
    m_movement_counter++;
    m_movement_counter = m_movement_counter % 50;

    if(m_movement_counter % 2 == 0){
        int entityVelX = m_accelx * time;
        int entityVelY = m_accely * time;
        if(entityVelX != 0 || entityVelY != 0 ){
            Point new_location = closestMovablePoint(Point(entityVelX, entityVelY), otherEntities);
            move(new_location.getX(), new_location.getY());
        }
    }
    
}