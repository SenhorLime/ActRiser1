/*
 * GameObject.cpp
 *
 *  Created on: Oct 9, 2023
 *      Author: joovi
 */

#include "GameObject.hpp"

void GameObject::SetSprites() {
  sprite.setTexture(*_texture);
}

void GameObject::UpdateDeltaTime(float &dt) {
  deltaTime = dt;
}

void GameObject::CropSprites(sf::IntRect spriteRect) {
  sprite.setTextureRect(spriteRect);
}

void GameObject::Draw(sf::RenderTarget *target) {
    sf::FloatRect rect;
    if (animacoes.size() == 0) {
        target->draw(sprite);
        rect = sprite.getGlobalBounds();
    } else {
        sprite = animatedSprite;
        target->draw(animatedSprite);
        rect = animatedSprite.getGlobalBounds();
    }

#ifdef FASE_TESTE
    sf::Vector2f a(rect.left, rect.top);
    sf::Vector2f b(rect.left + rect.width, rect.top);
    sf::Vector2f c(rect.left + rect.width, rect.top);
    sf::Vector2f d(rect.left + rect.width, rect.top + rect.height);
    sf::Vector2f e(rect.left + rect.width, rect.top + rect.height);
    sf::Vector2f f(rect.left, rect.top + rect.height);
    sf::Vector2f g(rect.left, rect.top + rect.height);
    sf::Vector2f h(rect.left, rect.top);
    sf::Vertex line[] = {a, b, c, d, e, f, g, h};
    target->draw(line, 8, sf::Lines);
#endif

}

GameObject::~GameObject() {}
