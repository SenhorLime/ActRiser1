#include "Arrow.hpp"
#include "../Game/ResourceLoader.hpp"
#include "../Game/Game.hpp"

sf::IntRect Arrow::rectShootUp(63, 18, 3, 14);
sf::IntRect Arrow::rectShootDown(60, 18, 3, 14);
sf::IntRect Arrow::rectShootRight(66, 29, 16, 3);
sf::IntRect Arrow::rectShootLeft(66, 26, 16, 3);

Arrow::Arrow(const sf::Vector2f &startPosition, sf::Vector2f &arrowDirection) :
		direction(arrowDirection) {
	sf::Vector2f v2fajustArrow;
	speed = 150.f;

	_texture = ResourceLoader::resourceLoader()->getTextura("Angel");

	SetSprites();

	sf::IntRect *rect = 0;

	if (arrowDirection.x == 0) {
		if (arrowDirection.y == 1) {
			rect = &rectShootDown;
			v2fajustArrow.x -= 5;
		} else {
			rect = &rectShootUp;
			v2fajustArrow.x += 5;
		}
	} else {
		if (arrowDirection.x == 1) {
			rect = &rectShootRight;
		} else {
			rect = &rectShootLeft;
		}
	}

	CropSprites(*rect);
	//SetScale(sf::Vector2f(0.65f, 0.65f));
	sprite.setPosition(startPosition + v2fajustArrow);

}

void Arrow::UpdateDeltaTime(float &dt) {
	Character::UpdateDeltaTime(dt);
	sf::Vector2f movement = direction * speed * deltaTime;
	MoveCharacther(movement);

	if (!getMyBounds().intersects(Game::getGame()->cameraBounds)) {
		this->ativo = false;
		std::cout<< "Eliminado" << std::endl;
	}
}

sf::Vector2f Arrow::GetDirection() {
	return direction;
}

void Arrow::SetDirection(sf::Vector2f &newDirection) {
	direction = newDirection;
}


