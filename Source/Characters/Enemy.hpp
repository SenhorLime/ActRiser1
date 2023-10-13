#pragma once

#include "./Character.hpp"

class Enemy : public Character {
public:
  enum Status {
    MoveUp,
    MoveDown,
    Stopped,
    MoveRight,
    MoveLeft,
    MoveUpRigth,
    MoveUpLeft,
    MoveDownRight,
    MoveDownLeft,
    takePeople,
    flee,
    burn
  };

  Enemy();

  Enemy(sf::Vector2f &position);

  void UpdateDeltaTime(float &dt) override;

  virtual int GetDamage();

protected:
  Status status;
  sf::Clock cooldownCount;
  float cooldownTime;
  float deltaTime;
  sf::Vector2f movement;
  int damage, spRecovery;

protected:
  virtual void initEnemy();

  virtual void MoveCharacter();

  virtual void setPosition(sf::Vector2f &position);

  virtual void SetMovementDirection(sf::Vector2f &direction);

  virtual bool saindoDaTela(sf::Vector2f &direction);

  virtual void voltarPraTela(sf::Vector2f &direction);

  virtual void goLeft();

  virtual void goRight();

  virtual void goDown();

  virtual void goUp();

  virtual void goStop();
};
