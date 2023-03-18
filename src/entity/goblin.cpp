#include "goblin.h"
#include <iostream>
#include "../utils/random.h"
#include <string>
#include "../graphics/spritefactory.h"

Goblin::Goblin(int x, int y) : Entity(Rectangle(x,y,10,10),  SpriteFactory::createRectangularSprite(
    SpriteFactory::SpriteType::RECTANGULAR, Rectangle(0,0,10,10), { 0, 128, 0, 255})), m_inMovement(0) {}


void Goblin::printEntityType(){
    std::cout<<"Goblin " << m_x << " " << m_y << std::endl;
}


void Goblin::setMovement(){

    if(!m_inMovement){
        int base_acceleration = 100;
        int rand = Random::randomInt(0,1);
        m_accelx = base_acceleration*rand;
        rand = Random::randomInt(0,1);
        m_accely = base_acceleration*rand;

        m_inMovement = 60;
    }else{
        m_inMovement -=1;
    }

    // std::cout << "Goblin Movement " << std::to_string(m_accelx)<< " " << std::to_string(m_accely) << std::endl;
    //std::cout << "Goblin location " << std::to_string(m_x)<< " " << std::to_string(m_y) << std::endl;
}