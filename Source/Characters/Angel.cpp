#include "Angel.hpp"
#include "../Game/Game.hpp"
#include "../Game/ResourceLoader.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/rect.hpp>

Angel::Angel() {
    cooldownTime = 1.f;
    speed = 95.f;
    deltaTime = 0;
    hitPoints = 8;
    pontos = 0;
    offset_x = 0;
    sprite.setPosition(200, 200);
    defineAnimacoes();
}

void Angel::defineAnimacoes() {
    //load of the texture image

    _texture = resourceLoader->getTextura("Angel");

    //Criando uma anima��o  para cada status
    //MoveUp, MoveDown, Stopped, MoveRight, MoveLeft, ShootUp, ShootDown, ShootRight, ShootLeft, SendPower

    Animation walkLeft(_texture);
    walkLeft.addFrames(sf::IntRect(86, 0, 13, 16), 1, 2);

    Animation walkRight(_texture);

    walkRight.addFrames(sf::IntRect(60, 0, 13, 16), 1, 2);

    Animation walkUp(_texture);
    walkUp.addFrames(sf::IntRect(30, 0, 15, 16), 1, 2);

    Animation walkDown(_texture);
    walkDown.addFrames(sf::IntRect(0, 0, 15, 16), 1, 2);

    Animation shootDown(_texture);
    shootDown.addFrames(sf::IntRect(0, 32, 16, 22), 1, 6);
    Animation shootUp(_texture);
    shootUp.addFrames(sf::IntRect(0, 54, 16, 20), 1, 6);
    Animation shootRight(_texture);
    shootRight.addFrames(sf::IntRect(0, 74, 23, 16), 1, 5);
    Animation shootLeft(_texture);
    shootLeft.addFrames(sf::IntRect(0, 90, 23, 16), 1, 5);
    Animation sendPower(_texture);
    sendPower.addFrames(sf::IntRect(0, 16, 16, 16), 1, 4);

    animacoes.insert({"MoveLeft", walkLeft});
    animacoes.insert({"MoveRight", walkRight});
    animacoes.insert({"MoveUp", walkUp});
    animacoes.insert({"MoveDown", walkDown});
    animacoes.insert({"ShootDown", shootDown});
    animacoes.insert({"ShootUp", shootUp});
    animacoes.insert({"ShootRight", shootRight});
    animacoes.insert({"ShootLeft", shootLeft});
    animacoes.insert({"SendPower", sendPower});

    //Cria o sprite animado.

    //std::map<std::string, Animation>::iterator it;

    animatedSprite.setAnimation(&(animacoes["MoveDown"]));
    shootDirection = sf::Vector2f(0.f, 1.f);

    animatedSprite.setFrameTime(sf::seconds(0.1));
    //animatedSprite.setScale(0.5,0.5);
    animatedSprite.play();
    animatedSprite.setOrigin(
        animatedSprite.getAnimation()->getRect(0).width / 2,
        animatedSprite.getAnimation()->getRect(0).height / 2);
    animatedSprite.setPosition(200, 200);
}

void Angel::MoveCharacter() {
    sf::Vector2f movement(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= 1.f;
        shootDirection = sf::Vector2f(-1.f, 0.f);
        CropSprites(sf::IntRect(58, 192, 35, 60));
        status = MoveLeft;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += 1.f;
        shootDirection = sf::Vector2f(1.f, 0.f);
        CropSprites(sf::IntRect(47, 67, 35, 60));
        status = MoveRight;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= 1.f;
        shootDirection = sf::Vector2f(0.f, -1.f);
        CropSprites(sf::IntRect(45, 5, 50, 60));
        status = MoveUp;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += 1.f;
        shootDirection = sf::Vector2f(0.f, 1.f);
        CropSprites(sf::IntRect(45, 128, 50, 60));
        status = MoveDown;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
        and (cooldownCount.getElapsedTime().asSeconds() >= cooldownTime)) {
        status = (status == MoveRight ? ShootRight :
                  status == MoveLeft ? ShootLeft :
                  status == MoveUp ? ShootUp : ShootDown);
    }
    SetMovementDirection(movement);
}

void Angel::ShootArrow(const sf::Vector2f &playerPosition) {
    if (cooldownCount.getElapsedTime().asSeconds() >= cooldownTime) {
        Arrow *arrow = new Arrow(playerPosition, shootDirection);
        Game::getGame()->charactersVector.push_back(arrow);
        Game::getGame()->arrowVector.push_back(arrow);
        cooldownCount.restart();
    }

    SoundManager::SoundPlayer()->PlaySoundEffect("Arrow");
}

void Angel::UpdateDeltaTime(float &dt) {

    Character::UpdateDeltaTime(dt);
    if (status == ShootDown or status == ShootUp or status == ShootLeft
        or status == ShootRight) {
        if (animatedSprite.getStatus() == animatedSprite.Playing)
            return;
        else {
            ShootArrow(GetPostion());
            status = (status == ShootRight ? MoveRight :
                      status == ShootLeft ? MoveLeft :
                      status == ShootUp ? MoveUp : MoveDown);
        }
    }

    MoveCharacter();
    animatedSprite.setFrameTime(sf::seconds(0.1));
    switch (status) { //MoveUp,MoveDown, Stopped, MoveRight, MoveLeft, ShootUp, ShootDown, ShootRight, ShootLeft, SendPower
        case Status::MoveUp:
            animatedSprite.setAnimation(&animacoes["MoveUp"]);
            animatedSprite.setLoop(true);
            break;
        case Status::MoveDown:
        case Status::Stopped:
            animatedSprite.setAnimation(&animacoes["MoveDown"]);
            animatedSprite.setLoop(true);
            break;
        case Status::MoveRight:
            animatedSprite.setAnimation(&animacoes["MoveRight"]);
            animatedSprite.setLoop(true);
            break;
        case Status::MoveLeft:
            animatedSprite.setAnimation(&animacoes["MoveLeft"]);
            animatedSprite.setLoop(true);
            break;
        case Status::ShootUp:
            animatedSprite.setAnimation(&animacoes["ShootUp"]);
            animatedSprite.setLoop(false);
            animatedSprite.setFrameTime(sf::seconds(0.03));
            break;
        case Status::ShootDown:
            animatedSprite.setAnimation(&animacoes["ShootDown"]);
            animatedSprite.setLoop(false);
            animatedSprite.setFrameTime(sf::seconds(0.03));
            break;
        case Status::ShootRight:
            animatedSprite.setAnimation(&animacoes["ShootRight"]);
            animatedSprite.setLoop(false);
            animatedSprite.setFrameTime(sf::seconds(0.03));
            break;
        case Status::ShootLeft:
            animatedSprite.setAnimation(&animacoes["ShootLeft"]);
            animatedSprite.setLoop(false);
            animatedSprite.setFrameTime(sf::seconds(0.03));
            break;
        case Status::SendPower:
            animatedSprite.setAnimation(&animacoes["SendPower"]);
            animatedSprite.setLoop(false);
            animatedSprite.setFrameTime(sf::seconds(0.03));
            break;
        default:
            //animatedSprite.setAnimation(&animacoes["MoveUp"]);
            break;
    }
    animatedSprite.play();
}

sf::Vector2f Angel::GetPostion() {
    if (animacoes.size() == 0)
        return sprite.getPosition();
    else
        return animatedSprite.getPosition();
}

void Angel::SetMovementDirection(sf::Vector2f &direction) {
    sf::Vector2f movement = direction * speed * deltaTime;
    sf::FloatRect sprRect = sprite.getGlobalBounds();
    sf::FloatRect camRect = Game::getGame()->cameraBounds;

    if ((sprRect.left + movement.x < 0)) {
        movement.x = 0;
    } else if (((sprRect.left + sprRect.width) + movement.x > camRect.width)) {
        movement.x = 0;
    }

    if ((sprRect.top + movement.y < 0)) {
        movement.y = 0;
    } else if (((sprRect.top + sprRect.height) + movement.y > camRect.height)) {
        movement.y = 0;
    }

    MoveCharacther(movement);
}

bool Angel::CanTakeDamage() {
    if (cooldownCount.getElapsedTime().asSeconds() >= cooldownTime) {
        cooldownCount.restart();
        return true;
    } else {
        return false;
    }
}