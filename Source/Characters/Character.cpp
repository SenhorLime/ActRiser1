#include "Character.hpp"

#include <iostream>

void Character::LoadTextures(std::string textureName) {
	texture = ResourceLoader::getResourceLoader()->getTextura(textureName);
}

void Character::SetSprites() {
	sprite.setTexture(*texture);
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
	} else {
		target->draw(animatedSprite);
	}
}

Character::~Character(){

}
