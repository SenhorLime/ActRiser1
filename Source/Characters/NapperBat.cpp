#include "NapperBat.hpp"
#include "../Game/Game.hpp"
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
void NapperBat::UpdateDeltaTime(float &dt) {
	Character::UpdateDeltaTime(dt);
	deltaTime = dt;
	MoveCharacter();

}

void NapperBat::MoveCharacter() {
	sf::Vector2f movement2 = movement * speed * deltaTime;

	if (saindoDaTela(movement2)){
	voltarPraTela(movement2);
	}
	else if((cooldownCount.getElapsedTime().asSeconds() >= cooldownTime)
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

void NapperBat::SetMovementDirection(sf::Vector2f &direction) {
	sf::Vector2f movement = direction * speed * deltaTime;
	sprite.move(movement);
	animatedSprite.move(movement);
}
bool NapperBat::saindoDaTela(sf::Vector2f &direction) {
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
void NapperBat::voltarPraTela(sf::Vector2f &direction) {

	sf::FloatRect sprRect = sprite.getGlobalBounds();
	sf::FloatRect camRect = Game::getGame()->cameraBounds;

	if ((sprRect.left + movement.x < 0)) {
		goRight();
	} else if (((sprRect.left + sprRect.width) + movement.x > camRect.width)) {
		goLeft();
	}else if ((sprRect.top + movement.y < 0)) {
		goDown();
	} else if (((sprRect.top + sprRect.height) + movement.y > camRect.height)) {
		goUp();
	}

}

void NapperBat::setPosition(sf::Vector2f &position) {
	animatedSprite.setPosition(position);
	sprite.setPosition(position);
}

void NapperBat::goLeft() {
	animatedSprite.setAnimation(&(animacoes["MoveLeft"]));
	movement.x = -1.0f;
	cooldownCount.restart();
	speed = 50.f;
	status = Status::MoveLeft;
}
void NapperBat::goRight() {
	animatedSprite.setAnimation(&(animacoes["MoveRight"]));
	movement.x = 1.0f;
	cooldownCount.restart();
	speed = 50.f;
	status = Status::MoveRight;
}
void NapperBat::goDown() {
	animatedSprite.setAnimation(&(animacoes["MoveDown"]));
	movement.y = 1.0f;
	cooldownCount.restart();
	speed = 50.f;
	status = Status::MoveDown;
}
void NapperBat::goUp() {
	animatedSprite.setAnimation(&(animacoes["MoveUp"]));
	movement.y = -1.0f;
	cooldownCount.restart();
	speed = 50.f;
	status = Status::MoveUp;
}
void NapperBat::goStop() {
	animatedSprite.setAnimation(&(animacoes["MoveDown"]));
	movement.y = 0; movement.x = 0;
	cooldownCount.restart();
	speed = 0;
	status = Status::Stopped;
}

void NapperBat::takeDemage(int value){
	Enemy::takeDemage(value);
}
