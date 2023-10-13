#pragma once

#include "Enemy.hpp"

class RedDemon : public Enemy {
public:
  RedDemon();

  RedDemon(sf::Vector2f &position);

private:
  void initEnemy();

  void MoveCharacter();
};
