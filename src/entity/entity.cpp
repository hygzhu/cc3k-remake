#include "entity.h"

Entity::Entity(Rectangle rect, std::shared_ptr<Sprite> sprite): 
 m_x(rect.getX()), 
 m_y(rect.getY()), 
  m_accelx(0), m_accely(0), 
  m_hitbox(Hitbox(Rectangle(0,0,rect.getWidth(), rect.getHeight()), Point(rect.getX(), rect.getY()))),
  m_sprite(sprite),
  m_status(Status()){
}


Entity::Entity(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite, Status status):
    m_x(p.getX()), 
    m_y(p.getY()), 
    m_accelx(0), m_accely(0), 
    m_hitbox(hitbox),
    m_sprite(sprite),
    m_status(status){}


bool Entity::collidable(){
    return false;
}

int & Entity::getAccelX(){ return m_accelx;}
int & Entity::getAccelY(){return m_accely;}

Hitbox Entity::getHitbox()
{
    return m_hitbox;
}


void Entity::setMovement(){
    //Do nothing if not overidden
}

void Entity::move(int dx, int dy) {
    m_x = dx;
    m_y = dy;
    m_hitbox.setPoint(Point(dx, dy));
}


void Entity::tryToMove(double time, std::vector<std::shared_ptr<Entity> > otherEntities)
{
    int entityVelX = m_accelx * time;
    int entityVelY = m_accely * time;
    if(entityVelX != 0 || entityVelY != 0 ){
        Point new_location = closestMovablePoint(Point(entityVelX, entityVelY), otherEntities);
        move(new_location.getX(), new_location.getY());
    }
}

Point Entity::closestMovablePoint(Point p, std::vector<std::shared_ptr<Entity> > otherEntities){
    int oldx = m_x;
    int oldy = m_y;

    int x = p.getX();
    int y = p.getY();

    Point moveable_location = Point(oldx, oldy);
    // non diagonal movements only
    if(x!=0 && y != 0)
    {   
        //even diagonal movements only
        if(std::abs(x) !=  std::abs(y)){
            return moveable_location;
        }
        for(int i =0; i<=std::abs(x); ++i){
            if(x > 0 && y > 0){
                if(doesEntityCollideAt(Point(oldx+i,oldy+i),otherEntities))
                {
                    // return moveable_location;
                    break;
                }else{
                    moveable_location.setX(oldx+i);
                    moveable_location.setY(oldy+i);
                }
            }
            if(x < 0 && y < 0){
                if(doesEntityCollideAt(Point(oldx-i,oldy-i),otherEntities))
                {
                    // return moveable_location;
                    break;
                }else{
                    moveable_location.setX(oldx-i);
                    moveable_location.setY(oldy-i);
                }
            }
            if(x > 0 && y < 0){
                if(doesEntityCollideAt(Point(oldx+i,oldy-i),otherEntities))
                {
                    // return moveable_location;
                    break;
                }else{
                    moveable_location.setX(oldx+i);
                    moveable_location.setY(oldy-i);
                }
            }
            if(x < 0 && y > 0){
                if(doesEntityCollideAt(Point(oldx-i,oldy+i),otherEntities))
                {
                    // return moveable_location;
                    break;
                }else{
                    moveable_location.setX(oldx-i);
                    moveable_location.setY(oldy+i);
                }
            }
        }
        // return moveable_location;
    }
    
    if(Point(oldx,oldy).distanceTo(Point(moveable_location.getX(), moveable_location.getY()))!=0){
        //std::cout << "Distance isnt zero" << std::endl;
        return moveable_location;
    }

    moveable_location = Point(oldx, oldy);

    // Try horizontal if diagonal dont work

    if((x!=0 && y == 0) || (x!=0 && y != 0)){
        //std::cout << "Try hor"<< std::endl;
        for(int i =0; i<=std::abs(x); ++i){
            if(x>0){

                if(doesEntityCollideAt(Point(oldx+i,oldy),otherEntities))
                {
                    // return moveable_location;
                    break;
                }else{
                    moveable_location.setX(oldx+i);
                }
            }else{
                if(doesEntityCollideAt(Point(oldx-i,oldy),otherEntities))
                {
                    // return moveable_location;
                    break;
                }else{
                    moveable_location.setX(oldx-i);
                }
            }
        }
    }

    if(Point(oldx,oldy).distanceTo(Point(moveable_location.getX(), moveable_location.getY()))!=0){
        //std::cout << " hori Distance isnt zero" << std::endl;
        //Point(moveable_location.getX(), moveable_location.getY()).print();
        return moveable_location;
    }


    moveable_location = Point(oldx, oldy);


    // Try vertical if diagonal dont work
    if((y!=0 && x == 0) || (x!=0 && y != 0)){
        //std::cout << "Try vert"<< std::endl;
        for(int i =0; i<=std::abs(y); ++i){
            if(y>0){
                if(doesEntityCollideAt(Point(oldx,oldy+i),otherEntities))
                {
                    // return moveable_location;
                    break;
                }else{
                    moveable_location.setY(oldy+i);
                }
            }else{
                if(doesEntityCollideAt(Point(oldx,oldy-i),otherEntities))
                {
                    // return moveable_location;
                    break;
                }else{
                    moveable_location.setY(oldy-i);
                }

            }
        }
    }

    return moveable_location;
}

bool Entity::doesEntityCollideAt(Point p, std::vector<std::shared_ptr<Entity> > otherEntities){

    Hitbox hitbox = m_hitbox;
    hitbox.setPoint(p);
    bool collidableEntityFound = false;


    for(const auto& otherEntity : otherEntities)
    {

        if(otherEntity.get() == this)
        {
            continue;
        }
        // Check if either rectangle not overlapping
        if (otherEntity->getHitbox().collidesWith(hitbox)) {
            //Collides

            // TODO: DOES NOT CAPTURE THE CASE WHERE > 1 RECTANGLE SURROUNDS
            if(otherEntity->collidable() && otherEntity->getHitbox().surrounds(hitbox)){
                // check if it surrounds
                collidableEntityFound = true;
                // std::cout << collidableEntityFound <<std::endl;
            }
            
            if(!otherEntity->collidable()){
                //std::cout << "non collidableEntityFound and collides -> tru" << std::endl;
                // otherEntity->printEntityType();
                return true;
            }
        }
    }

    // std::cout << "THE END" << std::endl;
    //std::cout << collidableEntityFound <<std::endl;
    if(collidableEntityFound){
        //std::cout << "can collid is true -> false" << std::endl;
        return false;
    }
    //std::cout << "cannot move" << std::endl;
    return true;
}



std::shared_ptr<Sprite> Entity::getSprite(){
    return m_sprite;
}


Status Entity::getStatus(){
    return m_status;
}

Point Entity::getPoint(){
    return Point(m_x, m_y);
}