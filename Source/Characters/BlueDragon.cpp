#include "BlueDragon.hpp"
#include "../Game/Game.hpp"
#include <ctime>
BlueDragon::BlueDragon() {
	initEnemy();
}
BlueDragon::BlueDragon(sf::Vector2f &position) {
	sf::Vector2f pt(200.f, 200.f);
	this->setPosition(position);
	initEnemy();
}

void BlueDragon::initEnemy() {
	speed = 50.f;
	hitPoints = 3;
	damage = 3;
	spRecovery = 2;
	cooldownTime = 1.5f;
	srand(time(0));

	//LoadTextures("Enemy");
	//SetSprites();
	//CropSprites(sf::IntRect(1, 2, 14, 14));
	//SetScale(sf::Vector2f(0.65f, 0.65f));

	_texture = ResourceLoader::getResourceLoader()->getTextura("Enemy");
	;

	Animation walkLeft(_texture);
	walkLeft.addFrames(sf::IntRect(142, 16, 19, 16), 1, 2);

	Animation walkRight(_texture);

	walkRight.addFrames(sf::IntRect(104, 16, 19, 16), 1, 2);

	Animation walkUp(_texture);
	walkUp.addFrames(sf::IntRect(0, 16, 26, 16), 1, 2);

	Animation walkDown(_texture);
	walkDown.addFrames(sf::IntRect(52, 16, 26, 16), 1, 2);
	animacoes.insert( { "MoveLeft", walkLeft });
	animacoes.insert( { "MoveRight", walkRight });
	animacoes.insert( { "MoveUp", walkUp });
	animacoes.insert( { "MoveDown", walkDown });

	//Cria o sprite animado.
	goStop();
	animatedSprite.setFrameTime(sf::seconds(0.1));
	//animatedSprite.setScale(0.5,0.5);
	animatedSprite.play();
	animatedSprite.setOrigin(
			animatedSprite.getAnimation()->getRect(0).width / 2,
			animatedSprite.getAnimation()->getRect(0).height / 2);

}

void BlueDragon::UpdateDeltaTime(float &dt) {
	Character::UpdateDeltaTime(dt);
	deltaTime = dt;
	MoveCharacter();

}

void BlueDragon::MoveCharacter() {
	sf::Vector2f movement2 = movement * speed * deltaTime;

	if (saindoDaTela(movement2)) {
		voltarPraTela(movement2);
	} else if ((cooldownCount.getElapsedTime().asSeconds() >= cooldownTime)) {
		int status = rand() % 12;
		movement.x = 0;
		movement.y = -0;
		switch (status) {
		case MoveUp:
			goUp();
			break;
		case MoveDown:
			goDown();
			break;
		case MoveLeft:
			goLeft();
			break;
		case MoveRight:
			goRight();
			break;
		case MoveUpRigth:
			goUpRigth();
			break;
		case MoveUpLeft:
			goUpLeft();
			break;
		case MoveDownRight:
			goDownRight();
			break;
		case MoveDownLeft:
			goDownLeft();
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

void BlueDragon::SetMovementDirection(sf::Vector2f &direction) {
	sf::Vector2f movement = direction * speed * deltaTime;
	sprite.move(movement);
	animatedSprite.move(movement);
}
bool BlueDragon::saindoDaTela(sf::Vector2f &direction) {
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
void BlueDragon::voltarPraTela(sf::Vector2f &direction) {

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

void BlueDragon::setPosition(sf::Vector2f &position) {
	animatedSprite.setPosition(position);
	sprite.setPosition(position);
}

void BlueDragon::goLeft() {
	animatedSprite.setAnimation(&(animacoes["MoveLeft"]));
	movement.x = -1.0f;
	cooldownCount.restart();
	speed = 50.f;
	status = Status::MoveLeft;
}
void BlueDragon::goRight() {
	animatedSprite.setAnimation(&(animacoes["MoveRight"]));
	movement.x = 1.0f;
	cooldownCount.restart();
	speed = 50.f;
	status = Status::MoveRight;
}
void BlueDragon::goDown() {
	animatedSprite.setAnimation(&(animacoes["MoveDown"]));
	movement.y = 1.0f;
	cooldownCount.restart();
	speed = 50.f;
	status = Status::MoveDown;
}
void BlueDragon::goUp() {
	animatedSprite.setAnimation(&(animacoes["MoveUp"]));
	movement.y = -1.0f;
	cooldownCount.restart();
	speed = 50.f;
	status = Status::MoveUp;
}
void BlueDragon::goStop() {
	animatedSprite.setAnimation(&(animacoes["MoveDown"]));
	movement.y = 0;
	movement.x = 0;
	cooldownCount.restart();
	speed = 0;
	status = Status::Stopped;
}
void BlueDragon::goUpRigth() {
	goUp();
	movement.x = 1.0f;
	status = Status::MoveUpRigth;
}
void BlueDragon::goUpLeft() {
	goUp();
	movement.x = -1.0f;
	status = Status::MoveUpLeft;
}
void BlueDragon::goDownRight() {
	goDown();
	movement.x = 1.0f;
	status = Status::MoveDownRight;
}
void BlueDragon::goDownLeft() {
	goDown();
	movement.x = -1.0f;
	status = Status::MoveDownLeft;
}


void BlueDragon::takeDemage(int value){
	Enemy::takeDemage(value);
}
