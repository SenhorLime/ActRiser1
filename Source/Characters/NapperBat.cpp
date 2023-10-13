#include "NapperBat.hpp"

NapperBat::NapperBat() {
    initEnemy();
}

NapperBat::NapperBat(sf::Vector2f &position) {
    sf::Vector2f pt(200.f, 200.f);
    this->setPosition(position);
    initEnemy();
}

void NapperBat::initEnemy() {
    speed = 50.f;
    hitPoints = 1;
    damage = 1;
    spRecovery = 1;
    cooldownTime = 3;
    srand(time(0));

    //LoadTextures("Enemy");
    //SetSprites();
    //CropSprites(sf::IntRect(1, 2, 14, 14));
    //SetScale(sf::Vector2f(0.65f, 0.65f));

    _texture = ResourceLoader::getResourceLoader()->getTextura("Enemy");


    Animation walkLeft(_texture);
    walkLeft.addFrames(sf::IntRect(164, 32, 12, 13), 1, 2);

    Animation walkRight(_texture);

    walkRight.addFrames(sf::IntRect(140, 32, 12, 13), 1, 2);

    Animation walkUp(_texture);
    walkUp.addFrames(sf::IntRect(0, 32, 35, 11), 1, 2);

    Animation walkDown(_texture);
    walkDown.addFrames(sf::IntRect(70, 32, 35, 11), 1, 2);

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

void NapperBat::MoveCharacter() {
    sf::Vector2f movement2 = movement * speed * deltaTime;

    if (saindoDaTela(movement2)) {
        voltarPraTela(movement2);
    } else if ((cooldownCount.getElapsedTime().asSeconds() >= cooldownTime)
        ) {
        int status = rand() % 6;
        movement.x = 0;
        movement.y = -0;
        switch (status) {
            case 0:
                goLeft();
                break;
            case 1:
                goRight();
                break;
            case 2:
                goUp();
                break;
            case 3:
                goDown();
                break;
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
