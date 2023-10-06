
#include "Nebulon.hpp"

Nebulon::Nebulon() {
	//cooldownTime = 2.f;
	speed = 15.f;
	deltaTime = 0;

	LoadTextures("Nebulon");
	SetSprites();
	CropSprites(sf::IntRect(1, 2, 14, 14));
	SetScale(sf::Vector2f(0.65f, 0.65f));
}
void Nebulon::UpdateDeltaTime(float &dt) {
	Character::UpdateDeltaTime(dt);
	MoveCharacter();
}

void Nebulon::MoveCharacter() {
	sf::Vector2f movement(0.f, 0.f);
	static int time = 0;
	time++;

	if (time <= 150) {
		movement.y += 2.f;

		if (time % 15 == 0 or time % 45 == 0) {
			CropSprites(sf::IntRect(1, 17, 14, 15));
		}

		if (time % 30 == 0 or time % 60 == 0) {
			CropSprites(sf::IntRect(1, 49, 14, 15));
		}

	} else if (time <= 300) {
		movement.y -= 2.f;

		if (time == 151) {
			CropSprites(sf::IntRect(17, 17, 14, 15));
		}

		if (time % 15 == 0 or time % 45 == 0) {
			CropSprites(sf::IntRect(17, 17, 14, 15));
		}

		if (time % 30 == 0 or time % 60 == 0) {
			CropSprites(sf::IntRect(17, 49, 14, 15));
		}

	} else if (time == 301) {
		time = 0;
		CropSprites(sf::IntRect(1, 1, 14, 15));
	}

	SetMovementDirection(movement);
}

void Nebulon::SetMovementDirection(sf::Vector2f &direction) {
	sf::Vector2f movement = direction * speed * deltaTime;
	sprite.move(movement);
}

void Nebulon::setPosition(sf::Vector2f &position){
	sprite.setPosition(position);
}
