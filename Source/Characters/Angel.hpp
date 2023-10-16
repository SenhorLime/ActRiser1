#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include "Character.hpp"
#include "Arrow.hpp"


class Angel : public Character {
public:
  enum Status {
    MoveUp,
    MoveDown,
    Stopped,
    MoveRight,
    MoveLeft,
    ShootUp,
    ShootDown,
    ShootRight,
    ShootLeft,
    SendPower
  };

  float offset_x;

  Status status = Stopped;

private:
  int pontos;
  float cooldownTime;
  sf::Vector2f shootDirection;
  sf::Clock cooldownCount;

public:
  Angel();

  void UpdateDeltaTime(float &dt) override;

  bool CanTakeDamage();

  sf::Vector2f GetPostion();

private:
  void SetMovementDirection(sf::Vector2f &direction);

  void defineAnimacoes();

  void MoveCharacter();

  void ShootArrow(const sf::Vector2f &playerPosition);
};
