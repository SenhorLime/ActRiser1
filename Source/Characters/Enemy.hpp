#pragma once

#include "./Character.hpp"

class Enemy : public Character {
public:
	Enemy();

	Enemy(sf::Vector2f &position);

	virtual void UpdateDeltaTime(float &dt) ;
	virtual void takeDemage(int);
protected:
	int hitPoints = 1, damage, spRecovery;
	void setPosition(sf::Vector2f &position);
	virtual void initEnemy();
	virtual void MoveCharacter();
	virtual void SetMovementDirection(sf::Vector2f &direction);
};
