#include "Arrow.hpp"

Arrow::Arrow(const sf::Vector2f &startPosition, sf::Vector2f &arrowDirection) : direction(arrowDirection) {
	position = startPosition;

	texture.setPosition(position);
	texture.setSize(sf::Vector2f(2.f, 2.f));
	texture.setFillColor(sf::Color::Red);
}

void Arrow::Update() {
	position += direction;
	texture.setPosition(position);
}

sf::Vector2f Arrow::GetDirection() {
	return direction;
}

void Arrow::SetDirection(sf::Vector2f &newDirection) {
	direction = newDirection;
}
