#ifndef MOVEMENT_H
#define MOVEMENT_H

class Entity;
class Point;

#include <memory>
#include <vector>

class Movement {
public:
  Movement(std::shared_ptr<Entity> entity, Point p, bool collidable);
  ~Movement(){};

  Point getPoint();
  bool collidable();
  virtual void setMovement();
  double &getAccelX();
  double &getAccelY();
  void move(double x, double y);
  virtual void tryToMove(double time,
                         std::vector<std::shared_ptr<Entity>> otherEntities);
  Point closestMovablePoint(Point p,
                            std::vector<std::shared_ptr<Entity>> otherEntities);
  bool isThereCollisionAtDestinationPoint(
      Point p, std::vector<std::shared_ptr<Entity>> otherEntities);
  virtual void triggerCollisionSideEffect(std::shared_ptr<Entity> other);
  void setInvincible(bool i);
  bool isInvincible() { return m_isInvincible; }
  void tick(double time);

protected:
  std::shared_ptr<Entity> m_entity;
  bool m_collidable;

  double m_accelx;
  double m_accely;
  int m_tick_count = 0;
  double m_time;
  bool m_isInvincible =
      false; // determines if we can trigger collision side effect
  double m_x;
  double m_y;
};

#endif