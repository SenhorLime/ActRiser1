<<<<<<< HEAD
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
}

void Character::CropSprites(sf::IntRect spriteRect) {
	sprite.setTextureRect(spriteRect);
}

void Character::SetScale(sf::Vector2f spriteScale) {
	sprite.setScale(spriteScale);
}

void Character::draw(sf::RenderTarget *target) {
	target->draw(sprite);
}
=======
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
}

void Character::CropSprites(sf::IntRect spriteRect) {
	sprite.setTextureRect(spriteRect);
}

void Character::SetScale(sf::Vector2f spriteScale) {
	sprite.setScale(spriteScale);
}

void Character::draw(sf::RenderTarget *target) {
	target->draw(sprite);
}
>>>>>>> branch 'main' of https://github.com/SenhorLime/ActRiser1.git
