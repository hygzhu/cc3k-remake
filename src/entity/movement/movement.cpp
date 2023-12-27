#include "movement.h"
#include "../../geometry/point.h"
#include "../entity.h"

Movement::Movement(std::shared_ptr<Entity> entity, Point p, bool collidable)
    : m_entity(entity), m_point(std::make_shared<Point>(p)), m_collidable(collidable),
      m_accelx(0), m_accely(0), m_time(0) {}

Point Movement::getPoint() { return Point(m_point->getX(), m_point->getY()); }


void Movement::setPoint(std::shared_ptr<Point> p) {m_point = p; }

bool Movement::collidable() { return m_collidable; }

void Movement::setMovement() {
  // Do nothing if not overidden
}

void Movement::move(int x, int y) {
  m_point->setX(x);
  m_point->setY(y);
}

void Movement::tick(double time) {
  m_time += time;

  // Set i frames
  const int i_frame_seconds = 2;
  if (m_time > i_frame_seconds) {
    m_isInvincible = false;
    int inttime = m_time;
    m_time = m_time - inttime;
  }
}

double &Movement::getAccelX() { return m_accelx; }
double &Movement::getAccelY() { return m_accely; }

void Movement::triggerCollisionSideEffect(std::shared_ptr<Entity> other) {
  // Do nothing by default
}

void Movement::setInvincible(bool i) { m_isInvincible = i; }

void Movement::tryToMove(double time,
                         std::vector<std::shared_ptr<Entity>> otherEntities) {
  tick(time);

  int entityVelX = m_accelx * time;
  int entityVelY = m_accely * time;
  if (entityVelX != 0 || entityVelY != 0) {
    Point new_location =
        closestMovablePoint(Point(entityVelX, entityVelY), otherEntities);
    move(new_location.getX(), new_location.getY());
  }
}

bool Movement::isThereCollisionAtDestinationPoint(
    Point p, std::vector<std::shared_ptr<Entity>> otherEntities) {

  Hitbox hitbox_copy = m_entity->getHitbox();
  auto hitbox_copy_point = hitbox_copy.getPoint();
  hitbox_copy_point->setX(p.getX());
  hitbox_copy_point->setY(p.getY());

  bool collidableEntityFound = false;

  for (const auto &otherEntity : otherEntities) {

    if (otherEntity.get() == m_entity.get()) {
      continue;
    }
    // Check if either rectangle not overlapping
    if (otherEntity->getHitbox().collidesWith(hitbox_copy)) {
      // Collides

      // TODO: DOES NOT CAPTURE THE CASE WHERE > 1 RECTANGLE SURROUNDS
      if (otherEntity->getMovement()->collidable() &&
          otherEntity->getHitbox().surrounds(hitbox_copy)) {
        // check if it surrounds
        collidableEntityFound = true;
        // // std::cout << collidableEntityFound <<std::endl;
      }

      if (!otherEntity->getMovement()->collidable()) {
        // // std::cout << "non collidableEntityFound and collides -> tru" <<
        // std::endl;
        //  otherEntity->printEntityType();
        //  Invoke collision
        triggerCollisionSideEffect(otherEntity);
        return true;
      }
    }
  }

  // // std::cout << "THE END" << std::endl;
  // // std::cout << collidableEntityFound <<std::endl;
  if (collidableEntityFound) {
    // // std::cout << "can collid is true -> false" << std::endl;
    return false;
  }
  return true;
}

Point Movement::closestMovablePoint(
    Point p, std::vector<std::shared_ptr<Entity>> otherEntities) {
  int oldx = m_point->getX();
  int oldy = m_point->getY();

  int x = p.getX();
  int y = p.getY();

  Point moveable_location = Point(oldx, oldy);
  // non diagonal movements only
  if (x != 0 && y != 0) {
    // even diagonal movements only
    if (std::abs(x) != std::abs(y)) {
      return moveable_location;
    }
    for (int i = 0; i <= std::abs(x); ++i) {
      if (x > 0 && y > 0) {
        if (isThereCollisionAtDestinationPoint(Point(oldx + i, oldy + i),
                                               otherEntities)) {
          // return moveable_location;
          break;
        } else {
          moveable_location.setX(oldx + i);
          moveable_location.setY(oldy + i);
        }
      }
      if (x < 0 && y < 0) {
        if (isThereCollisionAtDestinationPoint(Point(oldx - i, oldy - i),
                                               otherEntities)) {
          // return moveable_location;
          break;
        } else {
          moveable_location.setX(oldx - i);
          moveable_location.setY(oldy - i);
        }
      }
      if (x > 0 && y < 0) {
        if (isThereCollisionAtDestinationPoint(Point(oldx + i, oldy - i),
                                               otherEntities)) {
          // return moveable_location;
          break;
        } else {
          moveable_location.setX(oldx + i);
          moveable_location.setY(oldy - i);
        }
      }
      if (x < 0 && y > 0) {
        if (isThereCollisionAtDestinationPoint(Point(oldx - i, oldy + i),
                                               otherEntities)) {
          // return moveable_location;
          break;
        } else {
          moveable_location.setX(oldx - i);
          moveable_location.setY(oldy + i);
        }
      }
    }
    // return moveable_location;
  }

  if (Point(oldx, oldy)
          .distanceTo(
              Point(moveable_location.getX(), moveable_location.getY())) != 0) {
    // // std::cout << "Distance isnt zero" << std::endl;
    return moveable_location;
  }

  moveable_location = Point(oldx, oldy);

  // Try horizontal if diagonal dont work

  if ((x != 0 && y == 0) || (x != 0 && y != 0)) {
    // // std::cout << "Try hor"<< std::endl;
    for (int i = 0; i <= std::abs(x); ++i) {
      if (x > 0) {

        if (isThereCollisionAtDestinationPoint(Point(oldx + i, oldy),
                                               otherEntities)) {
          // return moveable_location;
          break;
        } else {
          moveable_location.setX(oldx + i);
        }
      } else {
        if (isThereCollisionAtDestinationPoint(Point(oldx - i, oldy),
                                               otherEntities)) {
          // return moveable_location;
          break;
        } else {
          moveable_location.setX(oldx - i);
        }
      }
    }
  }

  if (Point(oldx, oldy)
          .distanceTo(
              Point(moveable_location.getX(), moveable_location.getY())) != 0) {
    // // std::cout << " hori Distance isnt zero" << std::endl;
    // Point(moveable_location.getX(), moveable_location.getY()).print();
    return moveable_location;
  }

  moveable_location = Point(oldx, oldy);

  // Try vertical if diagonal dont work
  if ((y != 0 && x == 0) || (x != 0 && y != 0)) {
    // // std::cout << "Try vert"<< std::endl;
    for (int i = 0; i <= std::abs(y); ++i) {
      if (y > 0) {
        if (isThereCollisionAtDestinationPoint(Point(oldx, oldy + i),
                                               otherEntities)) {
          // return moveable_location;
          break;
        } else {
          moveable_location.setY(oldy + i);
        }
      } else {
        if (isThereCollisionAtDestinationPoint(Point(oldx, oldy - i),
                                               otherEntities)) {
          // return moveable_location;
          break;
        } else {
          moveable_location.setY(oldy - i);
        }
      }
    }
  }

  return moveable_location;
}