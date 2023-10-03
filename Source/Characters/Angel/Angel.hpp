#pragma once
//#ifndef ANIMATION_HPP_
//#define ANIMATION_HPP_

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include "../Characther_Parent/Character.hpp"
#include "Arrow/Arrow.hpp"


class Angel: public Character {
public:
	enum Status {
		MoveUp,
		MoveDown,
		Stopped,
		MoveRight,
		MoveLeft,
		ShootUp,
		ShootDown,
		ShootRight,
		ShootLeft,
		SendPower
	};

	sf::Clock cooldownCount;
	float cooldownTime;
	float offset_x;

	Status status = Stopped;

	int vidas;

private:
	int pontos;
	sf::Vector2f shootDirection;

public:
	Angel();

	virtual void UpdateDeltaTime(float &dt);

	sf::Vector2f GetPostion();

private:
	void SetMovementDirection(sf::Vector2f &direction);
	void defineAnimacoes();
	void MoveCharacter();
	void ShootArrow(const sf::Vector2f &playerPosition);


};
//#endif /* ANIMATION_HPP_ */
