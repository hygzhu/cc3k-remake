#include "commonroom.h"
#include "../entity/entityfactory.h"
#include "../utils/random.h"
#include <iostream>

CommonRoom::CommonRoom(BoundingRectangle rect): Room(rect){
    // Generate entities in room
    const int room_size = rect.getHeight()*rect.getWidth();
    const int block_size_per_entity = 50000;
    const int min_entities = 1;
    const int max_entities = room_size/block_size_per_entity;
    const int num_enemies = Random::randomInt(min_entities, max_entities);

    const int wall_buffer = 10;
    //rect.print();

    for(int i = 0; i<num_enemies; ++i){

        const int x = Random::randomInt(rect.getX()+wall_buffer, rect.getX() + rect.getWidth() - wall_buffer);
        const int y = Random::randomInt(rect.getY()+wall_buffer, rect.getY() + rect.getHeight() - wall_buffer);
        m_enemies.push_back(EntityFactory::createEntity(EntityFactory::EntityType::GOBLIN, x, y));
    }
    // std::cout << "Enemies generated: "<<  m_enemies.size() << std::endl;
}



std::vector<std::shared_ptr<Entity> > CommonRoom::getEntitiesToBeRendered(){

    std::vector<std::shared_ptr<Entity> > result;
    for(auto entity : m_entities){
        result.push_back(entity);
    }
    for(auto entity : m_enemies){
        result.push_back(entity);
    }
    return result;
}

std::vector<std::shared_ptr<Entity> > CommonRoom::getMovingEntities(){
    return m_enemies;
}