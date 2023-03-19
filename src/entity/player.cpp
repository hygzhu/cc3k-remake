
#include "player.h"
#include <iostream>
#include "enemy.h"


Player::Player(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite, Status stats): Entity(p, hitbox, sprite, stats)

{}



void Player::printEntityType(){
    std::cout<<"Player " << getHitbox().toString() <<  std::endl;
}


void Player::triggerCollisionSideEffect(std::shared_ptr<Entity> other){

    auto enemy = std::dynamic_pointer_cast<Enemy>(other);
    if(enemy != nullptr){
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