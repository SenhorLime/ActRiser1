/*
 * GameObject.hpp
 *
 *  Created on: Oct 9, 2023
 *      Author: joovi
 */

#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../Game/ResourceLoader.hpp"

class GameObject {
public:
	sf::Sprite sprite;

public:
	virtual void UpdateDeltaTime(float &dt);
	virtual void Draw(sf::RenderTarget *target);
	virtual ~GameObject();

protected:
	float deltaTime;
	sf::Texture *texture;
	sf::Clock deltaTimeClock;

protected:
	virtual void SetSprites();
	virtual void LoadTextures(std::string textureName);
	virtual void CropSprites(sf::IntRect spriteRect);
	virtual void SetScale(sf::Vector2f spriteScale);
};
