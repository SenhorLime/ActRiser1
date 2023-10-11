/*
 * GameObject.cpp
 *
 *  Created on: Oct 9, 2023
 *      Author: joovi
 */

#include "GameObject.hpp"

void GameObject::LoadTextures(std::string textureName) {
  texture = ResourceLoader::getResourceLoader()->getTextura(textureName);
}

void GameObject::SetSprites() {
  sprite.setTexture(*texture);
}

void GameObject::UpdateDeltaTime(float &dt) {
  deltaTime = dt;
}

void GameObject::SetScale(sf::Vector2f spriteScale) {
  sprite.setScale(spriteScale);
}

void GameObject::CropSprites(sf::IntRect spriteRect) {
  sprite.setTextureRect(spriteRect);
}

void GameObject::Draw(sf::RenderTarget *target) {
  target->draw(sprite);
}

GameObject::~GameObject() {}
