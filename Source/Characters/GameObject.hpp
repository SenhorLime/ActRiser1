/*
 * GameObject.hpp
 *
 *  Created on: Oct 9, 2023
 *      Author: joovi
 */

#pragma once
// #define FASE_TESTE

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Animation.hpp"
#include "../Game/SoundManager.hpp"
#include "../Game/ResourceLoader.hpp"

class GameObject {
public:
  bool ativo = true;
  sf::Sprite sprite;
  AnimatedSprite animatedSprite;
  std::map<std::string, Animation> animacoes;

public:
  virtual void UpdateDeltaTime(float &dt);

  virtual void Draw(sf::RenderTarget *target);

  virtual ~GameObject();

protected:
  float deltaTime;
  sf::Texture *_texture;
  ResourceLoader* resourceLoader = ResourceLoader::resourceLoader();

protected:
  virtual void SetSprites();

  virtual void CropSprites(sf::IntRect spriteRect);
};
