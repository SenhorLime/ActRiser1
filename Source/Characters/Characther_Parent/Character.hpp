#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Character {
public:
	sf::Sprite sprite;

public:
	virtual void UpdateDeltaTime(float &dt);

protected:
	sf::Texture texture;

	float speed;
	float deltaTime;

protected:
	virtual void SetSprites();
	virtual void LoadTextures(std::string filePath);
	virtual void CropSprites(sf::IntRect spriteRect);
	virtual void SetScale(sf::Vector2f spriteScale);
};
