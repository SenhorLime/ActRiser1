#include "Enemy.hpp"
#include "../Game/Game.hpp"

void Enemy::MoveCharacter() {}
void Enemy::initEnemy() {}

Enemy::Enemy() {
    initEnemy();
}

Enemy::Enemy(sf::Vector2f &position) {
    sprite.setPosition(position);
    initEnemy();
}

void Enemy::UpdateDeltaTime(float &dt) {
    Character::UpdateDeltaTime(dt);
    deltaTime = dt;
    MoveCharacter();
}

void Enemy::setPosition(sf::Vector2f &position) {
    animatedSprite.setPosition(position);
    sprite.setPosition(position);
}

void Enemy::SetMovementDirection(sf::Vector2f &direction) {
    sf::Vector2f movement = direction * speed * deltaTime;
    sprite.move(movement);
    animatedSprite.move(movement);
}

bool Enemy::saindoDaTela(sf::Vector2f &direction) {
    sf::FloatRect sprRect = sprite.getGlobalBounds();
    sf::FloatRect camRect = Game::getGame()->cameraBounds;
    if ((sprRect.left + direction.x < 0)
        or (((sprRect.left + sprRect.width) + direction.x > camRect.width))
        or ((sprRect.top + direction.y < 0))
        or (((sprRect.top + sprRect.height) + direction.y > camRect.height))) {
        return (true);
    }
    return false;
}

void Enemy::voltarPraTela(sf::Vector2f &direction) {

    sf::FloatRect sprRect = sprite.getGlobalBounds();
    sf::FloatRect camRect = Game::getGame()->cameraBounds;

    if ((sprRect.left + movement.x < 0)) {
        goRight();
    } else if (((sprRect.left + sprRect.width) + movement.x > camRect.width)) {
        goLeft();
    } else if ((sprRect.top + movement.y < 0)) {
        goDown();
    } else if (((sprRect.top + sprRect.height) + movement.y > camRect.height)) {
        goUp();
    }

}

void Enemy::goLeft() {
    animatedSprite.setAnimation(&(animacoes["MoveLeft"]));
    movement.x = -1.0f;
    cooldownCount.restart();
    speed = 50.f;
    status = Status::MoveLeft;
}

void Enemy::goRight() {
    animatedSprite.setAnimation(&(animacoes["MoveRight"]));
    movement.x = 1.0f;
    cooldownCount.restart();
    speed = 50.f;
    status = Status::MoveRight;
}

void Enemy::goDown() {
    animatedSprite.setAnimation(&(animacoes["MoveDown"]));
    movement.y = 1.0f;
    cooldownCount.restart();
    speed = 50.f;
    status = Status::MoveDown;
}

void Enemy::goUp() {
    animatedSprite.setAnimation(&(animacoes["MoveUp"]));
    movement.y = -1.0f;
    cooldownCount.restart();
    speed = 50.f;
    status = Status::MoveUp;
}

void Enemy::goStop() {
    animatedSprite.setAnimation(&(animacoes["MoveDown"]));
    movement.y = 0;
    movement.x = 0;
    cooldownCount.restart();
    speed = 0;
    status = Status::Stopped;
}

void Enemy::takeDemage(int value) {
    hitPoints -= value;
    if (hitPoints <= 0) {
        ativo = false;
    }
}
