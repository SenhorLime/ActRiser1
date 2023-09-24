#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Arrow {
private:
	sf::Vector2f position;
	sf::Vector2f direction;

	sf::Sprite sprite;
public:
	sf::RectangleShape texture;
	Arrow(const sf::Vector2f &startPosition, sf::Vector2f &arrowDirection);

	void Update();

	sf::Vector2f GetDirection();

	void SetDirection(sf::Vector2f &newDirection);

};
