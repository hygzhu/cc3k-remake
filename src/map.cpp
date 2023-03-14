#include "map.h"
#include "entity/entityfactory.h"
#include "room/roomfactory.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <tuple>
#include "utils/random.h"



Map::Map(std::shared_ptr<Entity> player, int numRooms, int roomMargin, int corridorWidth): player(player){

    std::cout << "Generating map with at most " << numRooms << " Rooms" << std::endl;

    const int VIEW_HEIGHT = 700;
    const int VIEW_WIDTH = 700;
    const int MAX_MAP_HEIGHT = 2000;
    const int MAX_MAP_WIDTH = 2000;
    width = VIEW_WIDTH;
    height = VIEW_HEIGHT;
    max_width = MAX_MAP_WIDTH;
    max_height = MAX_MAP_HEIGHT;

    const int starting_zone = 100;

    // Generate starting room
    std::cout << "Generating rooms" << std::endl;
    BoundingRectangle startRect(MAX_MAP_WIDTH/2, MAX_MAP_HEIGHT/2, starting_zone, starting_zone);
    std::shared_ptr<Room> room = RoomFactory::createRoom(RoomFactory::RoomType::STARTING, startRect);
    m_rooms.push_back(room);

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

    int margin = roomMargin;
    int maxAttempts = 1000; // Maximum number of attempts to generate a non-colliding rectangle
    int numRectangles = 0;
    int maxRectangles = numRooms;
    while (numRectangles < maxRectangles) {
        BoundingRectangle rect = generateRectangle(bounds, rectangles, margin);
        if(rect.getHeight() == 0 || rect.getWidth() ==0){
            break;
        }
        
        m_rooms.push_back(RoomFactory::createRoom(RoomFactory::RoomType::COMMON, rect));

        //std::cout << "Rectangle " << numRectangles << ": (" << rect.getX() << ", " << rect.getY() << ", " << rect.getWidth() << ", " << rect.getHeight() << ")" << std::endl;
        if (numRectangles >= maxAttempts) {
            std::cerr << "Unable to generate " << numRectangles << " non-colliding rectangles." << std::endl;
            return;
        }

        numRectangles++;
    }

    //paths
    generateCorridors(corridorWidth);
}

Map::~Map() {}


// Function to generate a random non-colliding rectangle within a larger rectangle
BoundingRectangle Map::generateRectangle(BoundingRectangle bounds, std::vector<BoundingRectangle>& rectangles, int margin) {
    
    BoundingRectangle rect(0,0,0,0);
    bool collides = false;
    int attempts = 0;
    do {
        attempts += 1;
        rect.setWidth(Random::randomInt(250, 750));
        rect.setHeight(Random::randomInt(250, 750));
        rect.setX(Random::randomInt(bounds.getX() + margin, bounds.getX() + bounds.getWidth() - margin - rect.getWidth()));
        rect.setY(Random::randomInt(bounds.getY() + margin, bounds.getY() + bounds.getHeight() - margin - rect.getHeight()));
        
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

    // std::cout << "CHECKING IF IT COLLIDES" <<std::endl;
    //Entity hit box
    BoundingRectangle newRect = entity->getBoundingRectangle();
    newRect.setX(x);
    newRect.setY(y);
    bool collidableEntityFound = false;

    for(const auto& otherEntity : getAllEntities())
    {

        if(otherEntity == entity)
        {
            continue;
        }
        // Check if either rectangle not overlapping
        if (otherEntity->getBoundingRectangle().isCollidingWith(newRect)) {
            //Collides
            // std::cout << "collides" <<std::endl;
            // entity->printEntityType();
            // otherEntity->printEntityType();

            // std::cout << otherEntity->collidable() <<std::endl;
            // std::cout << otherEntity->getBoundingRectangle().surrounds(newRect) <<std::endl;

            // TODO: DOES NOT CAPTURE THE CASE WHERE > 1 RECTANGLE SURROUNDS
            if(otherEntity->collidable() && otherEntity->getBoundingRectangle().surrounds(newRect)){
                // std::cout << "collidableEntityFound" << std::endl;
                //otherEntity->printEntityType();
                // check if it surrounds
                collidableEntityFound = true;

                // std::cout << collidableEntityFound <<std::endl;
            }
            
            if(!otherEntity->collidable()){
                // std::cout << "noncollidableEntityFound" << std::endl;
                // otherEntity->printEntityType();
                return true;
            }
        }
    }

    // std::cout << "THE END" << std::endl;
    //std::cout << collidableEntityFound <<std::endl;
    if(collidableEntityFound){
        //std::cout << "can collid is true" << std::endl;
        return false;
    }
    //std::cout << "cannot move" << std::endl;
    return true;
}


bool Map::canEntityMove(int x, int y, std::shared_ptr<Entity> entity)
{
    int oldx = entity->getX();
    int oldy = entity->getY();

    // non diagonal movements only
    //std::cout << x << " " << y << std::endl;
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
        //even diagonal movements only
        if(std::abs(x) !=  std::abs(y)){
            return moveable_location;
        }
        for(int i =0; i<=std::abs(x); ++i){
            if(x > 0 && y > 0){
                if(doesEntityCollideAt(oldx+i,oldy+i,entity))
                {
                    return moveable_location;
                }else{
                    moveable_location.first = oldx+i;
                    moveable_location.second = oldy+i;
                }
            }
            if(x < 0 && y < 0){
                if(doesEntityCollideAt(oldx-i,oldy-i,entity))
                {
                    return moveable_location;
                }else{
                    moveable_location.first = oldx-i;
                    moveable_location.second = oldy-i;
                }
            }
            if(x > 0 && y < 0){
                if(doesEntityCollideAt(oldx+i,oldy-i,entity))
                {
                    return moveable_location;
                }else{
                    moveable_location.first = oldx+i;
                    moveable_location.second = oldy-i;
                }
            }
            if(x < 0 && y > 0){
                if(doesEntityCollideAt(oldx-i,oldy+i,entity))
                {
                    return moveable_location;
                }else{
                    moveable_location.first = oldx-i;
                    moveable_location.second = oldy+i;
                }
            }
        }
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

std::vector<std::shared_ptr<Entity> > Map::getViewboxStaticEntities()
{
    std::vector<std::shared_ptr<Entity> > viewBoxEntities;

    // Render corridors first
    for(auto corridor : m_corridors)
    {
        for(const auto& wall : corridor->getEntities())
        {
            if(wall->getBoundingRectangle().isCollidingWith(getViewBox()))
            {
                viewBoxEntities.push_back(wall);
            }
        }
    }

    // Render rooms
    for(auto room : m_rooms)
    {
        //std::cout << "getEntitiesToBeRendered " << room->getEntitiesToBeRendered().size() << std::endl;
        //std::cout << "total entities " << room->getEntities().size() << std::endl;
        if(room->getBounds().isCollidingWith(getViewBox())){

            for(const auto& roomEntity : room->getNonMovingEntities())
            {
                if(roomEntity->getBoundingRectangle().isCollidingWith(getViewBox()))
                {
                    viewBoxEntities.push_back(roomEntity);
                }
            }
        }
    }

    return viewBoxEntities;

}


std::vector<std::shared_ptr<Entity> > Map::getViewboxMovingEntities()
{
    std::vector<std::shared_ptr<Entity> > viewBoxEntities;

    //render moving entities in rooms
    for(auto room : m_rooms)
    {
        //std::cout << "getEntitiesToBeRendered " << room->getEntitiesToBeRendered().size() << std::endl;
        //std::cout << "total entities " << room->getEntities().size() << std::endl;
        if(room->getBounds().isCollidingWith(getViewBox())){

            for(const auto& roomEntity : room->getMovingEntities())
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

void Map::generateCorridors(int corridorWidth)
{

    std::cout << "Generating corridors" << std::endl;
    if(m_rooms.size() < 2){
        return;
    }
    // get center coordinate of every room
    std::vector<std::pair<int, int>> coordinates;
    for(const auto room : m_rooms)
    {   
        Point point = room->getBounds().getCenterPoint();
        coordinates.push_back({point.getX(), point.getY()});
    }
    // get a minimum spanning tree with prims algorithm
    std::vector<std::vector<std::pair<int, int>>> adjList;

    int n = coordinates.size(); // number of coordinates

    // build adjacency list
    for (int i = 0; i < n; i++) {
        std::vector<std::pair<int, int>> partial;
        for (int j = 0; j < n; j++) {
            int dx = coordinates[i].first - coordinates[j].first;
            int dy = coordinates[i].second - coordinates[j].second;
            int dist = std::sqrt(dx * dx + dy * dy); // euclidean distance
            partial.push_back({j, dist});
        }
        adjList.push_back(partial);
    }

    // minimum spanning tree using Prim's algorithm
    std::vector<bool> visited(n, false);

    auto cmp = [](std::tuple<int, int, int> left,std::tuple<int, int, int> right) {
        return std::get<0>(left) > std::get<0>(right); // order elements by the values of their second components, in asc order
    };
    std::priority_queue<std::tuple<int, int, int > , std::vector<std::tuple<int, int, int > > , decltype(cmp) > pq(cmp); // min-heap of pairs (weight, vertex)
    std::vector<std::vector<std::pair<int, int > > >  mst; // minimum spanning tree

        pq.push(std::make_tuple<int,int,int>(0, 0, 0));

        while (!pq.empty()) {

            int node = std::get<1>(pq.top());
            int neighbour = std::get<2>(pq.top());
            int dist = std::get<0>(pq.top());
            pq.pop();
            if (visited[neighbour]) continue;

            visited[node] = true;
            if (node != neighbour){
                std::vector<std::pair<int, int>> edge;
                edge.push_back(coordinates[node]);
                edge.push_back(coordinates[neighbour]);
                // std::cout << node << " LOL " << curr_node << " "<< mst.size() << std::endl;
                mst.push_back(edge);
                visited[neighbour] = true;
            }
            
            for (int neighbour_index = 0; neighbour_index < coordinates.size(); ++neighbour_index) {
                
                // skip if our edges overlap with any exising edges in MST
                bool overlaps = false;
                Point a(coordinates[neighbour].first, coordinates[neighbour].second);
                Point b(coordinates[neighbour_index].first, coordinates[neighbour_index].second);
                for(auto edge : mst)
                {
                    Point c(edge[0].first, edge[0].second);
                    Point d(edge[1].first, edge[1].second);
                    bool intersect = Point::doLinesIntersect(a,b,c,d);
                    if(intersect)
                    {
                        Point intersection = Point::findIntersection(a,b,c,d);
                        if(!(a==intersection || b==intersection || c == intersection || d == intersection))
                        {
                            overlaps = true;
                        }
                    }
                    if(overlaps){
                        break;
                    }
                }
                //std::cout <<"neighbour_index " << neighbour_index << " !visited[neighbour_index] " << !visited[neighbour_index]  <<" !overlaps " <<!overlaps << std::endl;
                if (!visited[neighbour_index] and !overlaps) {
                    int new_dist = adjList[neighbour][neighbour_index].second;
                    auto tup= std::make_tuple<int,int,int>(0,0,0);
                    std::get<0>(tup) = new_dist;
                    std::get<1>(tup) = neighbour;
                    std::get<2>(tup) = neighbour_index;
                    pq.push(tup);
                }
            }
        }
    
    std::vector<Point> allDoorCenters;

    // For each pair we want to construct a path to the side pair
    // Get closest two points on a bounding rect to each pair, find closest wall n blocks away from both ends (now we have our door)
    for(auto pairs : mst){
        std::pair<int,int> pair1 = pairs[0];
        std::pair<int,int> pair2 = pairs[1];

        Point point1(pair1.first, pair1.second);
        Point point2(pair2.first, pair2.second);

        std::shared_ptr<Room> room1;
        std::shared_ptr<Room> room2;

        auto iter = std::find_if(m_rooms.begin(), m_rooms.end(), [point1](std::shared_ptr<Room> room) { return room->getBounds().getCenterPoint() == point1; });
        if (iter != m_rooms.end())
        {
            room1 = *iter;
            //std::cout << "Found room 1 " << std::endl;
        }
        iter = std::find_if(m_rooms.begin(), m_rooms.end(), [point2](std::shared_ptr<Room> room) { return room->getBounds().getCenterPoint() == point2; });
        if (iter != m_rooms.end())
        {
            room2 = *iter;
            //std::cout << "Found room 2" << std::endl;
        }

        // // Construct path from room1 to room2
        // // start point in room1
        Point start = room1->getBounds().getClosestPointTo(room2->getBounds().getCenterPoint());
        Point end = room2->getBounds().getClosestPointTo(start);
        //std::cout << "Start " << start<< " End "<< end << std::endl;
        allDoorCenters.push_back(start);
        allDoorCenters.push_back(end);


        auto comp = [end]( Point a, Point b ) { return a.distanceTo(end) > b.distanceTo(end); };
        auto rooms = m_rooms;
        int buffer = 50; // How wide our path needs to be
    
        // Run A* to get path from start to end 
        std::priority_queue<Point, std::vector<Point>, decltype( comp )> priority_queue(comp);
        std::vector<Point> path;
        std::unordered_map<std::string,std::string> seen;
        priority_queue.push(start);
        int visitedBlocks = 0;

        while(!priority_queue.empty())
        {
            if(visitedBlocks > max_height*max_width){
                //std::cout << "Could not find path" << std::endl;
                break;
            }

            Point curr = priority_queue.top();
            int distLeft = curr.distanceTo(end);
            priority_queue.pop();

            //only add to path if long enough
            if(distLeft >= corridorWidth/4 || distLeft == 0){
                path.push_back(curr);
            }

            seen.emplace(curr.toString(), curr.toString());

            if(curr == end){
                break;
            }


            std::vector<Point> neighbours;
            if(distLeft > corridorWidth/4){
                neighbours = curr.getSurroundingPointsNAway(corridorWidth/4);
            }else{
                neighbours = curr.getSurroundingPoints();
            }

            for(Point neighbour : neighbours)
            {
                auto search = seen.find(neighbour.toString());
                if(search == seen.end()){
                    //std::cout << neighbour.toString();

                    seen.emplace(neighbour.toString(), neighbour.toString());
                    priority_queue.push(neighbour);
                }
            }

            // }
        }
        //std::cout << "Path len " << path.size() << std::endl;


        if(path.size()==0){

            //std::cout << "Path len is 0, skipping"  << std::endl;
            break;
        }

        // Need to construct a path along this
        int corridor_width = corridorWidth;
        std::shared_ptr<Corridor> corridor = std::make_shared<Corridor>(path, corridor_width);

        m_corridors.push_back(corridor);
    }



}


void Map::updateAllMovableEntityLocations(double time){

    for(std::shared_ptr<Entity> movingEntity : getMovingEntities()){

        movingEntity->setMovement();
        int entityVelX = movingEntity->getAccelX() * time;
        int entityVelY = movingEntity->getAccelY() * time;

        // std::cout << time << " "<< entityVelX << " " <<  entityVelY << std::endl;
        if(entityVelX != 0 || entityVelY != 0 ){


            // std::cout << "OLD LOCATION AT "<< movingEntity->getX() << " " <<  movingEntity->getY() << std::endl;
            std::pair<int,int> new_location = movableLocationCloseTo(entityVelX,entityVelY,movingEntity);

            //  std::cout << "MOVING TO "<< new_location.first << " " <<  new_location.second << std::endl;
            movingEntity->move(new_location.first, new_location.second);
        }

    }
}


std::vector<std::shared_ptr<Entity> > Map::getMovingEntities()
{
    std::vector<std::shared_ptr<Entity>> result;
    result.push_back(player);
    for(std::shared_ptr<Room> room : m_rooms){
        for(auto entity : room->getMovingEntities()){
            result.push_back(entity);
        }
    }
    return result;
}


std::vector<std::shared_ptr<Entity> > Map::getAllEntities(){
    std::vector<std::shared_ptr<Entity>> result;

    result.push_back(player);
    //Rooms
    for(auto room : m_rooms)
    {
        for(const auto& roomEntity : room->getAllEntities())
        {
            result.push_back(roomEntity);
        }
        
    }

    // corridors
    for(auto corridor : m_corridors)
    {
        for(const auto& wall : corridor->getEntities())
        {
            result.push_back(wall);
        }
    }
    
    //Render misc entities
    for(auto entity : entities)
    {
        result.push_back(entity);
    }


    return result;
}