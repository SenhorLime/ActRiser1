#include "../Characther_Parent/Character.hpp"

#include <iostream>

void Character::LoadTextures(std::string filePath) {
	if (!texture.loadFromFile(filePath)) {
		std::cerr << "Falha os carregar o arquivo. Arquivo " << filePath
				<< " nao encontrado";
	} else {
		texture.loadFromFile(filePath);
	}
}

void Character::SetSprites() {
	sprite.setTexture(texture);
}

void Character::UpdateDeltaTime(float &dt) {
	deltaTime = dt;
	animatedSprite.update(sf::seconds(dt));
}

void Character::CropSprites(sf::IntRect spriteRect) {
	sprite.setTextureRect(spriteRect);
}

void Character::SetScale(sf::Vector2f spriteScale) {
	sprite.setScale(spriteScale);
}

void Character::Move(sf::Vector2f movement) {
	sprite.move(movement);
	animatedSprite.move(movement);
}

void Character::draw(sf::RenderTarget *target) {
	if (animacoes.size() == 0) {
		target->draw(sprite);
		std::cout << "Simples" << std::endl;
	} else {
		target->draw(animatedSprite);
		std::cout << "Animated" << std::endl;
	}

}
