#include "rat.h"
#include <iostream>
#include "../utils/random.h"
#include <string>
#include "../graphics/spritefactory.h"

Rat::Rat(int x, int y) : Entity(Rectangle(x,y,10,10),  SpriteFactory::createRectangularSprite(
    SpriteFactory::SpriteType::RECTANGULAR, Rectangle(0,0,10,10), { 79, 49, 4, 255})), m_inMovement(0)  {}


void Rat::printEntityType(){
    std::cout<<"Rat " << m_x << " " << m_y << std::endl;
}


void Rat::setMovement(){

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