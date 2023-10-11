#include "Character.hpp"
#include "Arrow.hpp"

#include <iostream>
#include <typeinfo>

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

void Character::MoveCharacther(sf::Vector2f movement) {
  sprite.move(movement);
  animatedSprite.move(movement);
}

void Character::Draw(sf::RenderTarget *target) {
  if (animacoes.size() == 0) {
    target->draw(sprite);
  } else {
    sprite = animatedSprite;
    target->draw(animatedSprite);
  }

  sf::Vector2f a(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);
  sf::Vector2f b(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width, sprite.getGlobalBounds().top);
  sf::Vector2f c(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width, sprite.getGlobalBounds().top);
  sf::Vector2f d(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width,
                 sprite.getGlobalBounds().top + sprite.getGlobalBounds().height);
  sf::Vector2f e(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width,
                 sprite.getGlobalBounds().top + sprite.getGlobalBounds().height);
  sf::Vector2f f(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height);
  sf::Vector2f g(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height);
  sf::Vector2f h(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);

  sf::Vertex line[] = {a, b, c, d, e, f, g, h};
  target->draw(line, 8, sf::Lines);


}

Character::~Character() {

}
