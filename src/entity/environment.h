#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "entity.h"

class Environment : public Entity {
public:
  Environment(int x, int y);
  virtual void printEntityType() override;
};

#endif
