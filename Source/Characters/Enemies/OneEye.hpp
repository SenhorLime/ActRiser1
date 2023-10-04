#pragma once

#include "../Characther_Parent/Character.hpp"

class OneEye : public Character {
public:
	OneEye();
	OneEye(sf::Vector2f &position);
	virtual void UpdateDeltaTime(float &dt);

private:
	void initEnemy();
	void MoveCharacter();
	void SetMovementDirection(sf::Vector2f &direction);
	void setPosition(sf::Vector2f &position);
};
