#pragma once

#include "../../Enemy.hpp"

class NapperBat : public Enemy {
public:
  NapperBat();

  NapperBat(sf::Vector2f &position);

private:
  void initEnemy() override;

  void MoveCharacter() override;
};
