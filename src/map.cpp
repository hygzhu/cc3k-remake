#include "map.h"
#include "entity/entityfactory.h"
#include "room/roomfactory.h"
#include "utils/random.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>

Map::Map(std::shared_ptr<Entity> player, int numRooms, int roomMargin,
         int corridorWidth)
    : player(player) {

  std::cout << "Generating map with at most " << numRooms << " Rooms"
            << std::endl;

  const int VIEW_HEIGHT = 720;
  const int VIEW_WIDTH = 1280;
  const int MAX_MAP_HEIGHT = 2000;
  const int MAX_MAP_WIDTH = 2000;
  width = VIEW_WIDTH;
  height = VIEW_HEIGHT;
  max_width = MAX_MAP_WIDTH;
  max_height = MAX_MAP_HEIGHT;

  const int starting_zone = 100;

  // Generate starting room
  std::cout << "Generating rooms" << std::endl;
  Rectangle startRect(MAX_MAP_WIDTH / 2, MAX_MAP_HEIGHT / 2, starting_zone,
                      starting_zone);
  std::shared_ptr<Room> room =
      RoomFactory::createRoom(RoomFactory::RoomType::STARTING, startRect);
  m_rooms.push_back(room);

  player->setPoint(Point(MAX_MAP_WIDTH / 2 + starting_zone / 2,
               MAX_MAP_HEIGHT / 2 + starting_zone / 2));
  entities.push_back(player);

  // Generate rest of dungeon
  // Set up the bounds of the larger rectangle
  Rectangle bounds = {0, 0, max_width, max_height};
  Rectangle existingRect = {MAX_MAP_WIDTH / 2, MAX_MAP_HEIGHT / 2,
                            starting_zone, starting_zone};

  // Generate non-colliding rectangles within the larger rectangle
  std::vector<Rectangle> rectangles;
  // add starting area
  rectangles.push_back(existingRect);

  int margin = roomMargin;
  int maxAttempts =
      1000; // Maximum number of attempts to generate a non-colliding rectangle
  int numRectangles = 0;
  int maxRectangles = numRooms;
  while (numRectangles < maxRectangles) {
    Rectangle rect = generateRectangle(bounds, rectangles, margin);
    if (rect.getHeight() == 0 || rect.getWidth() == 0) {
      break;
    }

    m_rooms.push_back(
        RoomFactory::createRoom(RoomFactory::RoomType::COMMON, rect));

    // std::cout << "Rectangle " << numRectangles << ": (" << rect.getX() << ",
    // " << rect.getY() << ", " << rect.getWidth() << ", " << rect.getHeight()
    // << ")" << std::endl;
    if (numRectangles >= maxAttempts) {
      std::cerr << "Unable to generate " << numRectangles
                << " non-colliding rectangles." << std::endl;
      return;
    }

    numRectangles++;
  }

  // paths
  generateCorridors(corridorWidth);
}

Map::~Map() {}

// Function to generate a random non-colliding rectangle within a larger
// rectangle
Rectangle Map::generateRectangle(Rectangle bounds,
                                 std::vector<Rectangle> &rectangles,
                                 int margin) {

  Rectangle rect(0, 0, 0, 0);
  bool collides = false;
  int attempts = 0;
  do {
    attempts += 1;
    rect.setWidth(Random::randomInt(250, 750));
    rect.setHeight(Random::randomInt(250, 750));
    rect.setX(Random::randomInt(bounds.getX() + margin,
                                bounds.getX() + bounds.getWidth() - margin -
                                    rect.getWidth()));
    rect.setY(Random::randomInt(bounds.getY() + margin,
                                bounds.getY() + bounds.getHeight() - margin -
                                    rect.getHeight()));

    // Check if the rectangle collides with any existing rectangles
    collides = false;
    for (const auto &r : rectangles) {

      Rectangle r_with_margin(r.getX() - margin, r.getY() - margin,
                              r.getWidth() + (2 * margin),
                              r.getHeight() + (2 * margin));
      if (rect.isCollidingWith(r_with_margin)) {
        collides = true;
        break;
      }
    }
    if (attempts > 50) {
      Rectangle invalid(0, 0, 0, 0);
      return invalid;
    }
  } while (collides);

  // Add the new rectangle to the vector of existing rectangles
  rectangles.push_back(rect);
  return rect;
}

std::vector<std::shared_ptr<Entity>> &Map::getEntities() { return entities; }

int Map::getWidth() { return width; }
int Map::getHeight() { return height; }

Rectangle Map::getViewBox() {
  const int middlex = player->getHitbox().getCenter().getX() +
                      player->getHitbox().getPoint()->getX();
  const int middley = player->getHitbox().getCenter().getX() +
                      player->getHitbox().getPoint()->getY();

  const int topleftx = middlex - (width / 2);
  const int toplefty = middley - (height / 2);

  Rectangle viewbox(topleftx, toplefty, width, height);
  // viewbox.print();
  return viewbox;
}

std::vector<std::shared_ptr<Entity>> Map::getViewboxStaticEntities() {
  std::vector<std::shared_ptr<Entity>> viewBoxEntities;

  // Render corridors first
  for (auto corridor : m_corridors) {
    for (const auto &floor : corridor->getEntities()) {
      if (floor->getHitbox().collidesWith(getViewBox())) {
        viewBoxEntities.push_back(floor);
      }
    }
  }

  // Render rooms
  for (auto room : m_rooms) {
    // std::cout << "getEntitiesToBeRendered " <<
    // room->getEntitiesToBeRendered().size() << std::endl; std::cout << "total
    // entities " << room->getEntities().size() << std::endl;
    if (room->getBounds().isCollidingWith(getViewBox())) {

      for (const auto &roomEntity : room->getNonMovingEntities()) {
        if (roomEntity->getHitbox().collidesWith(getViewBox())) {
          viewBoxEntities.push_back(roomEntity);
        }
      }
    }
  }
  // std::cout << "total entities " << viewBoxEntities.size() << std::endl;
  return viewBoxEntities;
}

std::vector<std::shared_ptr<Entity>> Map::getViewboxMovingEntities() {
  std::vector<std::shared_ptr<Entity>> viewBoxEntities;

  // render moving entities in rooms
  for (auto room : m_rooms) {

    // NOTE: Some entities will leave room, so we cannot render rooms that
    // collide with viewbox
    for (const auto &roomEntity : room->getMovingEntities()) {
      if (roomEntity->getHitbox().collidesWith(getViewBox())) {
        viewBoxEntities.push_back(roomEntity);
      }
    }
  }

  // Render misc entities (only player is here)
  for (auto entity : entities) {
    if (entity->getHitbox().collidesWith(getViewBox())) {
      viewBoxEntities.push_back(entity);
    }
  }

  return viewBoxEntities;
}

void Map::generateCorridors(int corridorWidth) {

  std::cout << "Generating corridors" << std::endl;
  if (m_rooms.size() < 2) {
    return;
  }
  // get center coordinate of every room
  std::vector<std::pair<int, int>> coordinates;
  for (const auto room : m_rooms) {
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

  auto cmp = [](std::tuple<int, int, int> left,
                std::tuple<int, int, int> right) {
    return std::get<0>(left) >
           std::get<0>(right); // order elements by the values of their second
                               // components, in asc order
  };
  std::priority_queue<std::tuple<int, int, int>,
                      std::vector<std::tuple<int, int, int>>, decltype(cmp)>
      pq(cmp); // min-heap of pairs (weight, vertex)
  std::vector<std::vector<std::pair<int, int>>> mst; // minimum spanning tree

  pq.push(std::make_tuple<int, int, int>(0, 0, 0));

  while (!pq.empty()) {

    int node = std::get<1>(pq.top());
    int neighbour = std::get<2>(pq.top());
    int dist = std::get<0>(pq.top());
    pq.pop();
    if (visited[neighbour])
      continue;

    visited[node] = true;
    if (node != neighbour) {
      std::vector<std::pair<int, int>> edge;
      edge.push_back(coordinates[node]);
      edge.push_back(coordinates[neighbour]);
      // std::cout << node << " LOL " << curr_node << " "<< mst.size() <<
      // std::endl;
      mst.push_back(edge);
      visited[neighbour] = true;
    }

    for (int neighbour_index = 0; neighbour_index < coordinates.size();
         ++neighbour_index) {

      // skip if our edges overlap with any exising edges in MST
      bool overlaps = false;
      Point a(coordinates[neighbour].first, coordinates[neighbour].second);
      Point b(coordinates[neighbour_index].first,
              coordinates[neighbour_index].second);
      for (auto edge : mst) {
        Point c(edge[0].first, edge[0].second);
        Point d(edge[1].first, edge[1].second);
        bool intersect = Point::doLinesIntersect(a, b, c, d);
        if (intersect) {
          Point intersection = Point::findIntersection(a, b, c, d);
          if (!(a == intersection || b == intersection || c == intersection ||
                d == intersection)) {
            overlaps = true;
          }
        }
        if (overlaps) {
          break;
        }
      }
      // std::cout <<"neighbour_index " << neighbour_index << "
      // !visited[neighbour_index] " << !visited[neighbour_index]  <<" !overlaps
      // " <<!overlaps << std::endl;
      if (!visited[neighbour_index] and !overlaps) {
        int new_dist = adjList[neighbour][neighbour_index].second;
        auto tup = std::make_tuple<int, int, int>(0, 0, 0);
        std::get<0>(tup) = new_dist;
        std::get<1>(tup) = neighbour;
        std::get<2>(tup) = neighbour_index;
        pq.push(tup);
      }
    }
  }

  std::vector<Point> allDoorCenters;

  // For each pair we want to construct a path to the side pair
  // Get closest two points on a bounding rect to each pair, find closest wall n
  // blocks away from both ends (now we have our door)
  for (auto pairs : mst) {
    std::pair<int, int> pair1 = pairs[0];
    std::pair<int, int> pair2 = pairs[1];

    Point point1(pair1.first, pair1.second);
    Point point2(pair2.first, pair2.second);

    std::shared_ptr<Room> room1;
    std::shared_ptr<Room> room2;

    auto iter = std::find_if(
        m_rooms.begin(), m_rooms.end(), [point1](std::shared_ptr<Room> room) {
          return room->getBounds().getCenterPoint() == point1;
        });
    if (iter != m_rooms.end()) {
      room1 = *iter;
      // std::cout << "Found room 1 " << std::endl;
    }
    iter = std::find_if(m_rooms.begin(), m_rooms.end(),
                        [point2](std::shared_ptr<Room> room) {
                          return room->getBounds().getCenterPoint() == point2;
                        });
    if (iter != m_rooms.end()) {
      room2 = *iter;
      // std::cout << "Found room 2" << std::endl;
    }

    // // Construct path from room1 to room2
    // // start point in room1
    Point start = room1->getBounds().getClosestPointTo(
        room2->getBounds().getCenterPoint());
    Point end = room2->getBounds().getClosestPointTo(start);
    allDoorCenters.push_back(start);
    allDoorCenters.push_back(end);

    auto comp = [end](Point a, Point b) {
      return a.distanceTo(end) > b.distanceTo(end);
    };
    auto rooms = m_rooms;
    int buffer = 50; // How wide our path needs to be

    // Run A* to get path from start to end
    std::priority_queue<Point, std::vector<Point>, decltype(comp)>
        priority_queue(comp);
    std::vector<Point> path;
    std::unordered_map<std::string, std::string> seen;
    priority_queue.push(start);
    int visitedBlocks = 0;

    while (!priority_queue.empty()) {
      if (visitedBlocks > max_height * max_width) {
        break;
      }

      Point curr = priority_queue.top();
      int distLeft = curr.distanceTo(end);
      priority_queue.pop();

      // only add to path if long enough
      if (distLeft >= corridorWidth / 4 || distLeft == 0) {
        path.push_back(curr);
      }

      seen.emplace(curr.toString(), curr.toString());

      if (curr == end) {
        break;
      }

      std::vector<Point> neighbours;
      if (distLeft > corridorWidth / 4) {
        neighbours = curr.getSurroundingPointsNAway(corridorWidth / 4);
      } else {
        neighbours = curr.getSurroundingPoints();
      }

      for (Point neighbour : neighbours) {
        auto search = seen.find(neighbour.toString());
        if (search == seen.end()) {
          // std::cout << neighbour.toString();

          seen.emplace(neighbour.toString(), neighbour.toString());
          priority_queue.push(neighbour);
        }
      }
    }

    if (path.size() == 0) {

      break;
    }

    // Need to construct a path along this
    int corridor_width = corridorWidth;
    std::shared_ptr<Corridor> corridor =
        std::make_shared<Corridor>(path, corridor_width);

    m_corridors.push_back(corridor);
  }
}

void Map::updateAllMovableEntityLocations(double time) {

  for (std::shared_ptr<Entity> movingEntity : getMovingEntities()) {

    movingEntity->getMovement()->setMovement();
    movingEntity->getMovement()->tryToMove(time, getAllEntities());
  }
}

std::vector<std::shared_ptr<Entity>> Map::getMovingEntities() {
  std::vector<std::shared_ptr<Entity>> result;
  result.push_back(player);
  for (std::shared_ptr<Room> room : m_rooms) {
    for (auto entity : room->getMovingEntities()) {
      result.push_back(entity);
    }
  }
  return result;
}

std::vector<std::shared_ptr<Entity>> Map::getAllEntities() {
  std::vector<std::shared_ptr<Entity>> result;

  result.push_back(player);
  // Rooms
  for (auto room : m_rooms) {
    for (const auto &roomEntity : room->getAllEntities()) {
      result.push_back(roomEntity);
    }
  }

  // corridors
  for (auto corridor : m_corridors) {
    for (const auto &wall : corridor->getEntities()) {
      result.push_back(wall);
    }
  }

  // Render misc entities
  for (auto entity : entities) {
    result.push_back(entity);
  }

  return result;
}