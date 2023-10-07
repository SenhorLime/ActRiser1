#pragma once

#include "./Character.hpp"

class Enemy : public Character {
public:
	Enemy();

	Enemy(sf::Vector2f &position);

	virtual void UpdateDeltaTime(float &dt) ;
protected:
	int hitPoints, damage, spRecovery;
	void initEnemy();
	void MoveCharacter();
	void SetMovementDirection(sf::Vector2f &direction);
	void setPosition(sf::Vector2f &position);
};
