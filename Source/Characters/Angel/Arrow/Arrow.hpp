#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../../Characther_Parent/Character.hpp"

class Arrow: public Character{
private:
	sf::Vector2f direction;
	static sf::IntRect rectShootUp,rectShootDown, rectShootRight, rectShootLeft;
public:

	Arrow(const sf::Vector2f &startPosition, sf::Vector2f &arrowDirection);

	virtual void UpdateDeltaTime(float &dt);

	sf::Vector2f GetDirection();

	void SetDirection(sf::Vector2f &newDirection);

	virtual void draw(sf::RenderTarget *target);

};
