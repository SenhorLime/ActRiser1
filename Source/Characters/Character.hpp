#pragma once

#include <string>
#include <map>
#include <vector>

#include "GameObject.hpp"
#include "Animation.hpp"
#include "../Game/ResourceLoader.hpp"

class Character : public GameObject {
public:
  bool ativo = true; // Vari�vel para retirar objeto do jogo.
  //Para anima��es
  AnimatedSprite animatedSprite;
  std::map<std::string, Animation> animacoes;


public:
  virtual sf::FloatRect getMyBounds();

  void UpdateDeltaTime(float &dt) override;

  void Draw(sf::RenderTarget *target) override;

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
