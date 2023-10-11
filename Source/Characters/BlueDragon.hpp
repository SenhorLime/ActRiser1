#pragma once

#include "Enemy.hpp"

class BlueDragon: public Enemy {
public:
	enum Status {
		MoveUp,
		MoveDown,
		Stopped,
		MoveRight,
		MoveLeft,
		MoveUpRigth,
		MoveUpLeft,
		MoveDownRight,
		MoveDownLeft,
		burn,
		flee
	};
	BlueDragon();
	BlueDragon(sf::Vector2f &position);

	virtual void UpdateDeltaTime(float &dt);
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
	void goUpRigth();
	void goUpLeft();
	void goDownRight();
	void goDownLeft();

};
