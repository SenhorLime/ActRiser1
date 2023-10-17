#include "Character.hpp"

sf::FloatRect Character::getMyBounds() {
    if (animacoes.size() == 0) {
        return sprite.getGlobalBounds();
    } else {
        return animatedSprite.getGlobalBounds();
    }
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

void Character::takeDamage(int value) {
    hitPoints -= value;
    if (hitPoints <= 0) {
        ativo = false;
    }
}

Character::~Character() {

}
