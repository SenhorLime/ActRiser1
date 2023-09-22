#pragma once

#include "../Characther_Parent/Character.hpp"

class OneEye : public Character {
public:
	OneEye();

	void MoveCharacter();
private:
	void SetMovementDirection(sf::Vector2f &direction);
};
