#include "Arrow.hpp"


sf::IntRect Arrow::rectShootUp(63, 18, 3, 14);
sf::IntRect Arrow::rectShootDown(60, 18, 3, 14);
sf::IntRect Arrow::rectShootRight(66, 29, 16, 3);
sf::IntRect Arrow::rectShootLeft(66, 26, 16, 3);

Arrow::Arrow(const sf::Vector2f &startPosition, sf::Vector2f &arrowDirection) :
		direction(arrowDirection) {

	speed = 150.f;

	//LoadTextures("Assets/Angel/angel.png");
	sf::Image image;
	if (!image.loadFromFile("Assets/Angel/angel.png")) {
		std::cerr << "Erro lendo imagem" << std::endl;
	}

	sf::Color cor(120, 144, 0);
	image.createMaskFromColor(cor);
	if (!	texture.loadFromImage(image)) {
		std::cerr << "Erro carregando textura" << std::endl;
	}
	texture.setSmooth(true);

	SetSprites();

	sf::IntRect *rect = 0;

	if (arrowDirection.x == 0) {
		if (arrowDirection.y == 1) {
			rect = &rectShootDown;
		} else {
			rect = &rectShootUp;
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
	sprite.setPosition(startPosition);

}

void Arrow::UpdateDeltaTime(float &dt) {
	Character::UpdateDeltaTime(dt);
	sf::Vector2f movement = direction * speed * deltaTime;
	Move(movement);
}

sf::Vector2f Arrow::GetDirection() {
	return direction;
}

void Arrow::SetDirection(sf::Vector2f &newDirection) {
	direction = newDirection;
}

void Arrow::draw(sf::RenderTarget *target){
	//Character::draw(target);
	target->draw(sprite);
}

