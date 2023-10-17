#pragma once

#include <string>
#include <map>
#include <vector>

#include "GameObject.hpp"

class Character : public GameObject {
public:
  virtual sf::FloatRect getMyBounds();

  void UpdateDeltaTime(float &dt) override;

  virtual void takeDamage(int);

  virtual ~Character();

protected:
  sf::Clock animationFrameTime;
  float speed;
  float deltaTime;
  sf::IntRect myBounds;
  int hitPoints;

protected:
  void CropSprites(sf::IntRect spriteRect) override;

  virtual void MoveCharacther(sf::Vector2f movement);
};
