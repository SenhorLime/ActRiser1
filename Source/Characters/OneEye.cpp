#include "OneEye.hpp"

OneEye::OneEye() {
	initEnemy();
}
OneEye::OneEye(sf::Vector2f &position) {
	sprite.setPosition(position);
	initEnemy();
}

void OneEye::initEnemy() {
	speed = 7.5f;
	deltaTime = 0;

	LoadTextures("OneEye");
	SetSprites();
	CropSprites(sf::IntRect(34, 2, 12, 14));
	SetScale(sf::Vector2f(0.65f, 0.65f));
}
;

void OneEye::UpdateDeltaTime(float &dt) {
	Character::UpdateDeltaTime(dt);
	MoveCharacter();
}

void OneEye::MoveCharacter() {
	sf::Vector2f movement(0.f, 0.f);
	static int time = 0;
	time++;

	if (time <= 150) {
		movement.x += 2.f;

		if (time % 15 == 0 or time % 45 == 0) {
			CropSprites(sf::IntRect(34, 17, 12, 14));
		}

		if (time % 30 == 0 or time % 60 == 0) {
			CropSprites(sf::IntRect(34, 49, 12, 14));
		}

	} else if (time <= 300) {
		movement.x -= 2.f;

		if (time == 151) {
			CropSprites(sf::IntRect(49, 17, 12, 14));
		}

		if (time % 15 == 0 or time % 45 == 0) {
			CropSprites(sf::IntRect(49, 17, 12, 14));
		}

		if (time % 30 == 0 or time % 60 == 0) {
			CropSprites(sf::IntRect(49, 49, 12, 14));
		}

	} else if (time == 301) {
		time = 0;
		CropSprites(sf::IntRect(34, 1, 12, 14));
		SetScale(sf::Vector2f(0.65f, 0.65f));
	}

	SetMovementDirection(movement);
}

void OneEye::SetMovementDirection(sf::Vector2f &direction) {
	sf::Vector2f movement = direction * speed * deltaTime;
	sprite.move(movement);
}

void OneEye::setPosition(sf::Vector2f &position) {
	sprite.setPosition(position);
}
