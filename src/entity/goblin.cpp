#include "goblin.h"
#include <iostream>
#include "../utils/random.h"
#include <string>

Goblin::Goblin(int x, int y) : Entity(x, y, 10, { 0, 128, 0, 255 }), m_inMovement(0) {}

void Goblin::move(int dx, int dy) {
    x_ = dx;
    y_ = dy;
}


void Goblin::printEntityType(){
    std::cout<<"Goblin " << x_ << " " << y_ << std::endl;
}


void Goblin::setMovement(){

    if(!m_inMovement){
        int base_acceleration = 100;
        int rand = Random::randomInt(-1,1);
        m_accelx = base_acceleration*rand;
        rand = Random::randomInt(-1,1);
        m_accely = base_acceleration*rand;

        m_inMovement = 60;
    }else{
        m_inMovement -=1;
    }

    // std::cout << "Goblin Movement " << std::to_string(m_accelx)<< " " << std::to_string(m_accely) << std::endl;
    //std::cout << "Goblin location " << std::to_string(x_)<< " " << std::to_string(y_) << std::endl;
}