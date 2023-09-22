#include "Angel.hpp"

#include <SFML/Window/Keyboard.hpp>

Angel::Angel() {
	speed = 75.f;
	deltaTime = 0;
	vidas = 5;
	pontos = 0;

	LoadTextures("Assets/Characters/Angel/Angel_Sheet.png");
	SetSprites();
	CropSprites(sf::IntRect(58, 192, 35, 60));
	SetScale(sf::Vector2f(0.2f, 0.2f));
}

void Angel::MoveCharacter() {
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		movement.y -= 1.f;
		CropSprites(sf::IntRect(45, 5, 50, 60));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		movement.y += 1.f;
		CropSprites(sf::IntRect(45, 128, 50, 60));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movement.x -= 1.f;
		CropSprites(sf::IntRect(58, 192, 35, 60));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		movement.x += 1.f;
		CropSprites(sf::IntRect(47, 67, 35, 60));
	}

	SetMovementDirection(movement);
}

void Angel::SetMovementDirection(sf::Vector2f &direction) {
	sf::Vector2f movement = direction * speed * deltaTime;
	sprite.move(movement);
}
