#pragma once

#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


class Character {
public:
	sf::Sprite sprite;


public:
	virtual void UpdateDeltaTime(float &dt);
	virtual void draw(sf::RenderTarget *target);
protected:
	sf::Texture texture;
	sf::Clock animationFrameTime;
	float speed;
	float deltaTime;

protected:
	virtual void SetSprites();
	virtual void LoadTextures(std::string filePath);
	virtual void CropSprites(sf::IntRect spriteRect);
	virtual void SetScale(sf::Vector2f spriteScale);

};
