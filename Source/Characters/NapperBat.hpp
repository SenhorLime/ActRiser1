#pragma once

#include "Enemy.hpp"

class NapperBat : public Enemy {
public:
	NapperBat();
	NapperBat(sf::Vector2f &position);

	virtual void UpdateDeltaTime(float &dt) ;
private:
	sf::Clock cooldownCount;
	float cooldownTime;
	float deltaTime;
	sf::Vector2f movement;

	void initEnemy();
	void MoveCharacter();
	void SetMovementDirection(sf::Vector2f &direction);
	void setPosition(sf::Vector2f &position);
	bool saindoDaTela(sf::Vector2f &direction);
	void voltarPraTela(sf::Vector2f &direction);

	void goLeft();
	void goRight();
	void goDown();
	void goUp();

};
