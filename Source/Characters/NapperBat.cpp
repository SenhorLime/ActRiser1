#include "NapperBat.hpp"

NapperBat::NapperBat() {
	initEnemy();
}
NapperBat::NapperBat(sf::Vector2f &position) {
	sf::Vector2f pt(200.f,200.f);
	this->setPosition(pt);
	initEnemy();
}

void NapperBat::initEnemy() {
	speed = 0;//75.f;
	hitPoints = 1;
	damage = 1;
	spRecovery = 1;

	//LoadTextures("Enemy");
	//SetSprites();
	//CropSprites(sf::IntRect(1, 2, 14, 14));
	//SetScale(sf::Vector2f(0.65f, 0.65f));

	texture = ResourceLoader::getResourceLoader()->getTextura("Enemy");

	Animation walkLeft(texture);
	walkLeft.addFrames(sf::IntRect(164, 32, 12, 13), 1, 2);

	Animation walkRight(texture);

	walkRight.addFrames(sf::IntRect(140, 32, 12, 13), 1, 2);

	Animation walkUp(texture);
	walkUp.addFrames(sf::IntRect(0, 32, 35, 11), 1, 2);

	Animation walkDown(texture);
	walkDown.addFrames(sf::IntRect(70, 32, 35, 11), 1, 2);

	animacoes.insert( { "MoveLeft", walkLeft });
	animacoes.insert( { "MoveRight", walkRight });
	animacoes.insert( { "MoveUp", walkUp });
	animacoes.insert( { "MoveDown", walkDown });

	//Cria o sprite animado.
	animatedSprite.setAnimation(&(animacoes["MoveDown"]));
	animatedSprite.setFrameTime(sf::seconds(0.1));
	//animatedSprite.setScale(0.5,0.5);
	animatedSprite.play();
	animatedSprite.setOrigin(
			animatedSprite.getAnimation()->getRect(0).width / 2,
			animatedSprite.getAnimation()->getRect(0).height / 2);

}

void NapperBat::UpdateDeltaTime(float &dt) {
	Character::UpdateDeltaTime(dt);
	MoveCharacter();
}

void NapperBat::MoveCharacter() {
	sf::Vector2f movement(0.f, 0.f);
	static int time = 0;
	time++;

	if (time <= 150) {
		int status = rand() % 4;
		switch (status) {
		case 0:
			animatedSprite.setAnimation(&(animacoes["MoveLeft"]));
			movement.x = -1.0f;
		break;
		case 1:
			animatedSprite.setAnimation(&(animacoes["MoveRight"]));
			movement.x = 1.0f;
			break;
		case 2:
			animatedSprite.setAnimation(&(animacoes["MoveUp"]));
			movement.y = -1.0f;
			break;
		case 3:
			animatedSprite.setAnimation(&(animacoes["MoveDown"]));
			movement.y = -1.0f;
			break;
		default:
			break;
		}
	}

	SetMovementDirection(movement);
}

void NapperBat::SetMovementDirection(sf::Vector2f &direction) {
	sf::Vector2f movement = direction * speed * deltaTime;
	sprite.move(movement);
}

void NapperBat::setPosition(sf::Vector2f &position) {
	sprite.setPosition(position);
}
