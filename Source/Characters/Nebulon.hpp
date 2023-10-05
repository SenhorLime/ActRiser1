#pragma once

#include "Character.hpp"

class Nebulon : public Character {
public:
	Nebulon();
	Nebulon(sf::Vector2f &position);

	virtual void UpdateDeltaTime(float &dt) ;
private:
	void initEnemy();
	void MoveCharacter();
	void SetMovementDirection(sf::Vector2f &direction);
	void setPosition(sf::Vector2f &position);
};
