#pragma once

#include "../Characther_Parent/Character.hpp"

class Nebulon : public Character {
public:
	Nebulon();

	void MoveCharacter();
private:
	void SetMovementDirection(sf::Vector2f &direction);
};
