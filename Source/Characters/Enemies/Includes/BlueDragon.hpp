#pragma once

#include "../../Enemy.hpp"

class BlueDragon : public Enemy {
public:
  BlueDragon();

  BlueDragon(sf::Vector2f &position);

private:
  void initEnemy();

  void MoveCharacter();

  void goUpRigth();

  void goUpLeft();

  void goDownRight();

  void goDownLeft();
};
