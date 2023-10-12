#pragma once

#include "Enemy.hpp"

class NapperBat : public Enemy {
public:
	enum Status {
			MoveUp,
			MoveDown,
			Stopped,
			MoveRight,
			MoveLeft,
			takePeople,
			flee
		};
	NapperBat();
	NapperBat(sf::Vector2f &position);

	virtual void UpdateDeltaTime(float &dt) ;
	virtual void takeDemage(int);
private:
	Status status;
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
	void goStop();

};
