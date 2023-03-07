#include "map.h"
#include "entityfactory.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <random>

// Function to generate a random integer within a range
int Map::randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}


// Function to generate a random non-colliding rectangle within a larger rectangle
BoundingRectangle Map::generateRectangle(BoundingRectangle bounds, std::vector<BoundingRectangle>& rectangles, int margin) {
    BoundingRectangle rect(0,0,0,0);
    bool collides = false;
    int attempts = 0;
    do {
        attempts += 1;
        rect.setWidth(randomInt(250, 500));
        rect.setHeight(randomInt(250, 500));
        rect.setX(randomInt(bounds.getX() + margin, bounds.getX() + bounds.getWidth() - margin - rect.getWidth()));
        rect.setY(randomInt(bounds.getY() + margin, bounds.getY() + bounds.getHeight() - margin - rect.getHeight()));
        
        // Check if the rectangle collides with any existing rectangles
        collides = false;
        for (const auto& r : rectangles) {

            BoundingRectangle r_with_margin(r.getX()-margin,r.getY()-margin, r.getWidth()+ (2*margin), r.getHeight() + (2*margin));
            if (rect.isCollidingWith(r_with_margin)) {
                collides = true;
                break;
            }
        }
        if(attempts > 50)
        {
            BoundingRectangle invalid(0,0,0,0);
            return invalid;
        }
    } while (collides);
    
    // Add the new rectangle to the vector of existing rectangles
    rectangles.push_back(rect);
    return rect;
}


Map::Map(std::shared_ptr<Entity> player): player(player){

    const int MAP_HEIGHT = 700;
    const int MAP_WIDTH = 700;
    const int MAX_MAP_HEIGHT = 2000;
    const int MAX_MAP_WIDTH = 2000;
    width = MAP_WIDTH;
    height = MAP_HEIGHT;
    max_width = MAX_MAP_WIDTH;
    max_height = MAX_MAP_HEIGHT;

    const int starting_zone = 100;

    // Generate starting room
    BoundingRectangle startRect(MAX_MAP_WIDTH/2, MAX_MAP_HEIGHT/2, starting_zone, starting_zone);
    m_rooms.push_back(std::make_shared<Room>(startRect));

    player->setX(MAX_MAP_WIDTH/2 + starting_zone/2);
    player->setY(MAX_MAP_HEIGHT/2 + starting_zone/2);
    entities.push_back(player);


    // Generate rest of dungeon
    // Set up the bounds of the larger rectangle
    BoundingRectangle bounds = {0, 0, max_width, max_height};
    BoundingRectangle existingRect = {MAX_MAP_WIDTH/2, MAX_MAP_HEIGHT/2, starting_zone, starting_zone};
    
    // Generate non-colliding rectangles within the larger rectangle
    std::vector<BoundingRectangle> rectangles;
    //add starting area
    rectangles.push_back(existingRect);

    int margin = 50;
    int maxAttempts = 1000; // Maximum number of attempts to generate a non-colliding rectangle
    int numRectangles = 0;
    while (numRectangles < 50) {
        numRectangles++;
        BoundingRectangle rect = generateRectangle(bounds, rectangles, margin);
        if(rect.getHeight() == 0 || rect.getWidth() ==0){
            break;
        }
        
        m_rooms.push_back(std::make_shared<Room>(rect));

        std::cout << "Rectangle " << numRectangles+1 << ": (" << rect.getX() << ", " << rect.getY() << ", " << rect.getWidth() << ", " << rect.getHeight() << ")" << std::endl;
        if (numRectangles >= maxAttempts) {
            std::cerr << "Unable to generate " << numRectangles << " non-colliding rectangles." << std::endl;
            return;
        }
    }
}

Map::~Map() {}


std::vector<std::shared_ptr<Entity> > & Map::getEntities()
{
    return entities;
}

int Map::getWidth()
{
    return width;
}
int Map::getHeight()
{
    return height;
}

bool Map::doesEntityCollideAt(int x, int y, std::shared_ptr<Entity> entity)
{
    //Entity hit box
    int entity_x = x;
    int entity_y = y;
    int entity_x2 = entity_x + entity->getSize()-1;
    int entity_y2 = entity_y + entity->getSize()-1;

    for(const auto& otherEntity : getViewboxEntities())
    {
        if(otherEntity == entity)
        {
            continue;
        }
        int other_entity_x = otherEntity->getX();
        int other_entity_y = otherEntity->getY();
        int other_entity_x2 = other_entity_x + otherEntity->getSize()-1;
        int other_entity_y2 = other_entity_y + otherEntity->getSize()-1;

        // Check if either rectangle not overlapping
        if (!(
            (entity_x2 < other_entity_x || other_entity_x2 < entity_x) 
            || (entity_y2 < other_entity_y || other_entity_y2 < entity_y)
            )) {
            //Collides
            //std::cout <<  "Curr " << entity_x << " " << entity_y << " " << entity_x2 << " " << entity_y2 <<std::endl;
            //std::cout << "Other "  << other_entity_x << " " << other_entity_y << " " << other_entity_x2 << " " << other_entity_y2 <<std::endl;
            otherEntity->printEntityType();
            return true;
        }
    }
    return false;
}


bool Map::canEntityMove(int x, int y, std::shared_ptr<Entity> entity)
{
    int oldx = entity->getX();
    int oldy = entity->getY();

    // non diagonal movements only
    std::cout << x << " " << y << std::endl;
    if(x!=0 && y != 0)
    {
        return false;

    }
    if(x!=0){
        y = entity->getY();
        for(int i =0; i<=std::abs(x); ++i){
            //std::cout <<"Checking if it collides at " << std::min(oldx+x, oldx)+i << " " << y << std::endl;
            if(doesEntityCollideAt(std::min(oldx+x, oldx)+i,y,entity))
            {
                return false;
            }
        }
    } else if(y!=0){
        x = entity->getX();
        for(int i =0; i<=std::abs(y); ++i){
            //std::cout <<"Checking if it collides at " << x << " " << std::min(oldy+y, oldy)+i << std::endl;
            if(doesEntityCollideAt(x,std::min(oldy+y, oldy)+i,entity))
            {
                return false;
            }
        }
    }

    //std::cout << "Can move"<< std::endl;
    return true;
}


std::pair<int,int> Map::movableLocationCloseTo(int x, int y, std::shared_ptr<Entity> entity)
{
    int oldx = entity->getX();
    int oldy = entity->getY();

    std::pair<int,int> moveable_location = std::make_pair(oldx, oldy);
    // non diagonal movements only
    //std::cout << x << " " << y << std::endl;
    if(x!=0 && y != 0)
    {
        return moveable_location;

    }

    if(x!=0){
        y = entity->getY();
        for(int i =0; i<=std::abs(x); ++i){
            //std::cout <<"Checking if it collides at " << std::min(oldx+x, oldx)+i << " " << y << std::endl;
            if(x>0){
                if(doesEntityCollideAt(oldx+i,y,entity))
                {
                    return moveable_location;
                }else{
                    moveable_location.first = oldx+i;
                }
            }else{
                if(doesEntityCollideAt(oldx-i,y,entity))
                {
                    return moveable_location;
                }else{
                    moveable_location.first = oldx-i;
                }
            }
        }
    } else if(y!=0){
        x = entity->getX();
        for(int i =0; i<=std::abs(y); ++i){
            //std::cout <<"Checking if it collides at " << x << " " << std::min(oldy+y, oldy)+i << std::endl;
            if(y>0){
                if(doesEntityCollideAt(x,oldy+i,entity))
                {
                    return moveable_location;
                }else{
                    moveable_location.second = oldy+i;
                }
            }else{
                if(doesEntityCollideAt(x,oldy-i,entity))
                {
                    return moveable_location;
                }else{
                    moveable_location.second = oldy-i;
                }

            }
        }
    }

    //std::cout << "Can move"<< std::endl;
    return moveable_location;
}


BoundingRectangle Map::getViewBox()
{
    const int middlex = player->getX()+ (player->getSize()/2);
    const int middley = player->getY() + (player->getSize()/2);

    const int topleftx = middlex - (width/2);
    const int toplefty = middley - (height/2);

    BoundingRectangle viewbox(topleftx,toplefty, width,height);
    return viewbox;
}

std::vector<std::shared_ptr<Entity> > Map::getViewboxEntities()
{
    std::vector<std::shared_ptr<Entity> > viewBoxEntities;

    // Render rooms
    for(auto room : m_rooms)
    {
        if(room->getBounds().isCollidingWith(getViewBox())){
            for(const auto& roomEntity : room->getEntities())
            {
                if(roomEntity->getBoundingRectangle().isCollidingWith(getViewBox()))
                {
                    viewBoxEntities.push_back(roomEntity);
                }
            }
        }
    }
    
    //Render misc entities
    for(auto entity : entities)
    {
        if(entity->getBoundingRectangle().isCollidingWith(getViewBox())){
            viewBoxEntities.push_back(entity);
        }
    }


    return viewBoxEntities;

}
