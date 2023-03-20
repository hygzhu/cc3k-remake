
#include "player.h"
#include "enemy.h"
#include <iostream>

Player::Player(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite,
               Status stats)
    : Entity(p, hitbox, sprite, stats)

{}

void Player::printEntityType() {
  std::cout << "Player " << getHitbox().toString() << std::endl;
}

// }