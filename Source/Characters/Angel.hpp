#pragma once

#include <SFML/System/Vector2.hpp>
#include "Characther_Parent/Character.hpp"

class Angel: public Character {
public:
	Angel();

	void MoveCharacter();
private:
	void SetMovementDirection(sf::Vector2f &direction);

public:
	int vidas;

private:
	int pontos;
};
