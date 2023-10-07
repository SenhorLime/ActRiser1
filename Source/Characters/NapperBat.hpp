#pragma once

#include "Enemy.hpp"

class NapperBat : public Enemy {
public:
	NapperBat();
	NapperBat(sf::Vector2f &position);

	virtual void UpdateDeltaTime(float &dt) ;
private:
	void initEnemy();
	void MoveCharacter();
	void SetMovementDirection(sf::Vector2f &direction);
	void setPosition(sf::Vector2f &position);
};
