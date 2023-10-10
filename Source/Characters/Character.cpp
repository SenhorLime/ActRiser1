#include "Character.hpp"
#include "Arrow.hpp"
#include "NapperBat.hpp"

#include <iostream>
#include <typeinfo>

void Character::LoadTextures(std::string textureName) {
	texture = ResourceLoader::getResourceLoader()->getTextura(textureName);
}

void Character::SetSprites() {
	sprite.setTexture(*texture);
}

sf::FloatRect Character::getMyBounds() {
	if (animacoes.size() == 0) {
	return sprite.getGlobalBounds();
	} else {
		return animatedSprite.getGlobalBounds();
	}

	 //if (typeid(*this) == typeid(Arrow)) {std::cout<< "Arrow" << std::endl;}
}

void Character::UpdateDeltaTime(float &dt) {
	deltaTime = dt;
	animatedSprite.update(sf::seconds(dt));
}

void Character::CropSprites(sf::IntRect spriteRect) {
	myBounds = spriteRect;
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
	sf::FloatRect rect;
	if (animacoes.size() == 0) {
		target->draw(sprite);
		rect = sprite.getGlobalBounds();
	} else {
		sprite = animatedSprite;
		target->draw(animatedSprite);
		rect = animatedSprite.getGlobalBounds();
	}

	sf::Vector2f a(rect.left, rect.top);
	sf::Vector2f b(rect.left+rect.width, rect.top);
	sf::Vector2f c(rect.left+rect.width, rect.top);
	sf::Vector2f d(rect.left+rect.width, rect.top + rect.height);
	sf::Vector2f e(rect.left+rect.width, rect.top + rect.height);
	sf::Vector2f f(rect.left, rect.top+ rect.height);
	sf::Vector2f g(rect.left, rect.top+ rect.height);
	sf::Vector2f h(rect.left, rect.top);
	if (typeid(*this) == typeid(NapperBat)) {
	std::cout<< "rect[" << rect.left<<","<< rect.top<<","<< rect.width<<","<< rect.height<<"]"<<std::endl;
	}
	sf::Vertex line[] = { a,b,c,d, e, f, g,h};
	target->draw(line, 8, sf::Lines);


}

Character::~Character() {

}
