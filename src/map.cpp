#include "map.h"
#include "entityfactory.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <utility>
#include <queue>
#include <cmath>
#include <unordered_map>

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

    //paths
    generateCorridors();
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

void Map::generateCorridors()
{
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

    // for (auto coord: coordinates) {
    //         std::cout << coord.first << " " << coord.second <<std::endl;

    // }

    // build adjacency list
    adjList.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dx = coordinates[i].first - coordinates[j].first;
            int dy = coordinates[i].second - coordinates[j].second;
            int dist = std::abs(std::sqrt(dx * dx + dy * dy)); // euclidean distance
            adjList[i].push_back({j, dist});
            adjList[j].push_back({i, dist});
        }
    }
    // for (const auto& vec : adjList) {
    //     for (const auto& elem : vec) {
    //         std::cout << "(" << elem.first << ", " << elem.second << ") ";
    //     }
    //     std::cout << std::endl;
    // }

    // minimum spanning tree using Prim's algorithm
    std::vector<bool> visited(n, false);
    std::priority_queue<std::pair<int, int > , std::vector<std::pair<int, int > > , std::greater<std::pair<int, int > > > pq; // min-heap of pairs (weight, vertex)
    std::vector<std::vector<std::pair<int, int > > >  mst; // minimum spanning tree
    for (int curr_node = 0; curr_node < n; curr_node++) {
        if (visited[curr_node]) continue;

        pq.push({curr_node,0});

        // std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq_copy = pq;
        // std::cout << "Priorty :" ;
        // while (!pq_copy.empty()) {
        //     std::pair<int, int> element = pq_copy.top();
        //     std::cout<< element.first << " " << element.second ;
        //     pq_copy.pop();
        // }
        // std::cout << std::endl;

        while (!pq.empty()) {
            // std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq_copy = pq;
            // std::cout << "Priorty :" ;
            // while (!pq_copy.empty()) {
            //     std::pair<int, int> element = pq_copy.top();
            //     std::cout  << element.first << " " << element.second ;
            //     pq_copy.pop();
            // }
            // std::cout << std::endl;

            int node = pq.top().first;
            int dist = pq.top().second;
            pq.pop();
            if (visited[node]) continue;
            visited[node] = true;
            if (node != curr_node){
                std::vector<std::pair<int, int>> edge;
                edge.push_back(coordinates[node]);
                edge.push_back(coordinates[curr_node]);
                // std::cout << node << " LOL " << curr_node << " "<< mst.size() << std::endl;
                mst.push_back(edge);
            }
            for (int neighbour_index = 0; neighbour_index < adjList[node].size(); ++neighbour_index) {
                if (!visited[neighbour_index]) {
                    pq.push({neighbour_index, adjList[node][neighbour_index].second});
                }
            }
            curr_node = node;
        }
    }
    // print minimum spanning tree
    for (auto pairs : mst) {
        std::cout << "pairs: ";
        for (auto coord : pairs) {
            std::cout << "("<< coord.first << "," << coord.second  << ") ";
        }
        std::cout <<  std::endl;
    }

    // For each pair we want to construct a path to the side pair
    // Get closest two points on a bounding rect to each pair, find closest wall n blocks away from both ends (now we have our door)
    for(auto pairs : mst){
        std::pair<int,int> pair1 = pairs[0];
        std::pair<int,int> pair2 = pairs[1];

        Point point1(pair1.first, pair1.second);
        Point point2(pair2.first, pair2.second);
        point1.print();
        point2.print();

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
        auto start = room1->getBounds().getClosestPointTo(room2->getBounds().getCenterPoint());
        auto end = room2->getBounds().getClosestPointTo(room1->getBounds().getCenterPoint());
        std::cout << "Start " << start<< " End "<< end << std::endl;

        auto comp = [end]( Point a, Point b ) { return a.distanceTo(end) > b.distanceTo(end); };
        auto rooms = m_rooms;

        // TODO: weird case where nothing is valid and a* terminates early, also sometimes when it goes forever????
        auto isValid = [rooms](Point p){
            for(auto room : rooms){
                if(room->getBounds().getClosestPointTo(p) == p){
                    return false;
                }
            }
            return true;
        };
        // Run A* to get path from start to end 
        std::priority_queue<Point, std::vector<Point>, decltype( comp )> priority_queue(comp);
        std::vector<Point> path;
        std::unordered_map<std::string,std::string> seen;
        priority_queue.push(start);
        while(!priority_queue.empty())
        {
            Point curr = priority_queue.top();
            priority_queue.pop();
            std::cout << "curr: ";
            curr.print();
            std::cout << "end: ";
            end.print();
            path.push_back(curr);

            seen.emplace(curr.toString(), curr.toString());

            if(curr == end){
                break;
            }


            std::vector<Point> neighbours;
            int x = curr.getX(), y = curr.getY();
            neighbours.push_back(Point(x, y+1)); // up
            neighbours.push_back(Point(x, y-1)); // down
            neighbours.push_back(Point(x-1, y)); // left
            neighbours.push_back(Point(x+1, y)); // right
            neighbours.push_back(Point(x+1, y+1));
            neighbours.push_back(Point(x+1, y-1));
            neighbours.push_back(Point(x-1, y+1));
            neighbours.push_back(Point(x-1, y-1));
            for(Point neighbour : neighbours)
            {
                auto search = seen.find(neighbour.toString());
                if(isValid(neighbour) || neighbour == end){
                    if(search == seen.end()){
                        std::cout << neighbour.toString();

                        seen.emplace(neighbour.toString(), neighbour.toString());
                        priority_queue.push(neighbour);
                    }
                }
            }
            std::cout << std::endl;
            // if(priority_queue.size() >= 10)
            // {
            // break;
            // }else
            // {
            //     // auto pq(priority_queue);
            //     // while (!pq.empty()) {
            //     // Point p = pq.top();
            //     // pq.pop();
            //     // std::cout << "(" << p.getX() << ", " << p.getY() << ") ";
            //     // }
            //     // std::cout <<  std::endl;
            // }
        }
        std::cout << "Path len " << path.size() << std::endl;
        break;
        


    }

}