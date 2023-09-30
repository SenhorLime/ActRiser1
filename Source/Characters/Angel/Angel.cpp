#include "Angel.hpp"
#include "../../Game/Game.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/rect.hpp>

Angel::Angel() {
	cooldownTime = 0.5f;
	speed = 75.f;
	deltaTime = 0;
	vidas = 8;
	pontos = 0;
	offset_x = 0;

	LoadTextures("Assets/Characters/Angel/Angel_Sheet.png");
	//LoadTextures("Assets/Tilesets/original/soanjo.png");
	SetSprites();
	CropSprites(sf::IntRect(58, 192, 35, 60));
	SetScale(sf::Vector2f(0.2f, 0.2f));

	sprite.setOrigin(sprite.getLocalBounds().width / 2,
			sprite.getLocalBounds().height / 2);

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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
			and cooldownCount.getElapsedTime().asSeconds() >= cooldownTime) {
		Arrow arrow(playerPosition, shootDirection);
		arrows.push_back(arrow);
		cooldownCount.restart();
	}
}

void Angel::SetMovementDirection(sf::Vector2f &direction) {
	sf::Vector2f movement = direction * speed * deltaTime;
	sf::FloatRect sprRect = sprite.getGlobalBounds();
	sf::FloatRect camRect = Game::getGame()->cameraBounds;
	//std::cout << "T" << sprRect.top << " L" << sprRect.left << " W"<< sprRect.width << " H" << sprRect.height << std::endl;


	if ((sprRect.left + movement.x < 0)) {
		movement.x = 0;
	} else if (((sprRect.left + sprRect.width) + movement.x > camRect.width)) {
		movement.x = 0;
	}

	if ((sprRect.top + movement.y < 0)) {
		movement.y = 0;
	} else if (((sprRect.top + sprRect.height) + movement.y > camRect.height)) {
		movement.y = 0;
	}

	sprite.move(movement);
}
