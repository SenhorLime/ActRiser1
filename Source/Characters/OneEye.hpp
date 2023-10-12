#pragma once

#include "Enemy.hpp"

class OneEye : public Enemy {
public:
	OneEye();
	OneEye(sf::Vector2f &position);
	virtual void UpdateDeltaTime(float &dt);
	void takeDemage(int value);
private:
	void initEnemy();
	void MoveCharacter();
	void SetMovementDirection(sf::Vector2f &direction);
	void setPosition(sf::Vector2f &position);
};
