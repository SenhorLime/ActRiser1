
#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include "../Characther_Parent/Character.hpp"
#include "Arrow/Arrow.hpp"

class Angel: public Character {
public:
	sf::Clock cooldownCount;
	float cooldownTime;
	float  offset_x;

	Angel();


	void MoveCharacter();
	void ShootArrow(const sf::Vector2f &playerPosition);
private:
	void SetMovementDirection(sf::Vector2f &direction);

public:
	int vidas;
	std::vector<Arrow> arrows;

	sf::Vector2f GetPostion() {
		return sprite.getPosition();
	}

private:
	int pontos;
	sf::Vector2f shootDirection;
};
