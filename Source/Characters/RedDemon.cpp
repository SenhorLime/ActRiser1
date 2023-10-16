#include "RedDemon.hpp"

RedDemon::RedDemon() {
    initEnemy();
}

RedDemon::RedDemon(sf::Vector2f &position) {
    sf::Vector2f pt(200.f, 200.f);
    this->setPosition(position);
    initEnemy();
}

void RedDemon::initEnemy() {
    speed = 40.f;
    hitPoints = 4;
    damage = 6;
    spRecovery = 4;
    cooldownTime = 1;
    srand(time(0));

    //LoadTextures("Enemy");
    //SetSprites();
    //CropSprites(sf::IntRect(1, 2, 14, 14));
    //SetScale(sf::Vector2f(0.65f, 0.65f));

    _texture = resourceLoader->getTextura("Enemy");

    Animation walkLeft(_texture);
    walkLeft.addFrames(sf::IntRect(90, 0, 15, 16), 1, 2);

    Animation walkRight(_texture);

    walkRight.addFrames(sf::IntRect(60, 0, 15, 16), 1, 2);

    Animation walkUp(_texture);
    walkUp.addFrames(sf::IntRect(0, 0, 15, 16), 1, 2);

    Animation walkDown(_texture);
    walkDown.addFrames(sf::IntRect(30, 0, 15, 16), 1, 2);

    animacoes.insert({"MoveLeft", walkLeft});
    animacoes.insert({"MoveRight", walkRight});
    animacoes.insert({"MoveUp", walkUp});
    animacoes.insert({"MoveDown", walkDown});

    //Cria o sprite animado.
    goStop();
    animatedSprite.setFrameTime(sf::seconds(0.1));
    //animatedSprite.setScale(0.5,0.5);
    animatedSprite.play();
    animatedSprite.setOrigin(
        animatedSprite.getAnimation()->getRect(0).width / 2,
        animatedSprite.getAnimation()->getRect(0).height / 2);

}


void RedDemon::MoveCharacter() {
    sf::Vector2f movement2 = movement * speed * deltaTime;

    if (saindoDaTela(movement2)) {
        voltarPraTela(movement2);
    } else if ((cooldownCount.getElapsedTime().asSeconds() >= cooldownTime)
        ) {
        int status = rand() % 10;
        movement.x = 0;
        movement.y = -0;
        switch (status) {
            case MoveLeft:
                goLeft();
                break;
            case MoveRight:
                goRight();
                break;
            case MoveUp:
                goUp();
                break;
            case MoveDown:
                goDown();
                break;
            case Stopped:
            default:
                goStop();
                break;
        }
        cooldownCount.restart();
        movement2 = movement * speed * deltaTime;
        //std::cout<< "Dentro" << std::endl;
    }

    SetMovementDirection(movement);
}
