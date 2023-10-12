#pragma once

#include "Enemy.hpp"

class Nebulon : public Enemy {
public:
	Nebulon();
	Nebulon(sf::Vector2f &position);

	virtual void UpdateDeltaTime(float &dt) ;
	void takeDemage(int);
private:
	void initEnemy();
	void MoveCharacter();
	void SetMovementDirection(sf::Vector2f &direction);
	void setPosition(sf::Vector2f &position);
};
