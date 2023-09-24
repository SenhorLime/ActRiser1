#include "Angel.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

Angel::Angel() {
	cooldownTime = 0.5f;
	speed = 75.f;
	deltaTime = 0;
	vidas = 8;
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
		shootDirection = sf::Vector2f(0.f, -1.f);
		CropSprites(sf::IntRect(45, 5, 50, 60));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		movement.y += 1.f;
		shootDirection = sf::Vector2f(0.f, 1.f);
		CropSprites(sf::IntRect(45, 128, 50, 60));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movement.x -= 1.f;
		shootDirection = sf::Vector2f(-1.f, 0.f);
		CropSprites(sf::IntRect(58, 192, 35, 60));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		movement.x += 1.f;
		shootDirection = sf::Vector2f(1.f, 0.f);
		CropSprites(sf::IntRect(47, 67, 35, 60));
	}

	SetMovementDirection(movement);
}

void Angel::ShootArrow(const sf::Vector2f &playerPosition) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and cooldownCount.getElapsedTime().asSeconds() >= cooldownTime) {
		Arrow arrow(playerPosition, shootDirection);
		arrows.push_back(arrow);
		cooldownCount.restart();
	}
}

void Angel::SetMovementDirection(sf::Vector2f &direction) {
	sf::Vector2f movement = direction * speed * deltaTime;
	sprite.move(movement);
}
