#include "goblin.h"
#include <iostream>
#include "../utils/random.h"
#include <string>
#include "../graphics/spritefactory.h"

Goblin::Goblin(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite):
 Entity(p, hitbox, sprite),  m_inMovement(0) {}


void Goblin::printEntityType(){
    std::cout<<"Goblin " << m_x << " " << m_y << std::endl;
}


void Goblin::setMovement(){

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
        m_restPoint = Random::randomInt(0,60);

    }else{
        m_inMovement -=1;
        //rest
        if(m_inMovement < m_restPoint){

        m_accely = 0;
        m_accelx = 0;
        }
    }

    // std::cout << "Goblin Movement " << std::to_string(m_accelx)<< " " << std::to_string(m_accely) << std::endl;
    //std::cout << "Goblin location " << std::to_string(m_x)<< " " << std::to_string(m_y) << std::endl;
}