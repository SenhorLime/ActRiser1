#include "Game.hpp"
#include "Collision.hpp"
#include "./ResourceLoader.hpp"

#include <iostream>
#include <cstddef> //For nullptr_t

Game *Game::instance = nullptr;
;

Game::Game() :
		player(nullptr) {
	window = new sf::RenderWindow();
	window->create(sf::VideoMode(1280, 720), "ActRaiser77");
	window->setMouseCursorVisible(false);
	window->setFramerateLimit(60);

	sf::Music backgroundMusic;

}

Game* Game::getGame() {
	if (instance == nullptr) {
		instance = new Game();
	}
	return instance;
}

void Game::GameMusic(sf::Music *backgroundMusic) {
	//backgroundMusic.openFromFile("Assets/Music/Monster.ogg");
	backgroundMusic->play();
	backgroundMusic->setVolume(50);
	backgroundMusic->setLoop(true);
}

void Game::carregaAssets() {
	ResourceLoader *resources = ResourceLoader::getResourceLoader();

	sf::Image image;
	if (!image.loadFromFile("Assets/Angel/angel.png")) {
		std::cerr << "Erro carregando imagem angel.png" << std::endl;
	}
	sf::Color cor(120, 144, 0);
	image.createMaskFromColor(cor);
	sf::Texture _textura;
	_textura.loadFromImage(image);

	resources->addTextura("Angel", _textura);
	resources->addTextura("OneEye",
			"Assets/Characters/Enemies/OneEye_Sheet.png");
	resources->addTextura("Nebulon_Sheet",
			"Assets/Characters/Enemies/Nebulon_Sheet.png");
	resources->addTextura("Enemy", "Assets/Enemy/Enemy.png");

	resources->addMusics("musicFilmore",
			"Assets/Music/15-Birth-of-the-People.ogg");

}

void Game::Init() {

	carregaAssets();

	//-------------------Controle do Mapa ------------------------//
	//todo[mover pra classe do mapa]
	auto &ldtkLevel0 = this->GameMap.world->getLevel("Level_0");

	// Load the TileMap from the level
	GameMap.Load(ldtkLevel0);

	// Get the layer of Entities
	auto &charactherSpawns = ldtkLevel0.getLayer("Spanws");

	ldtk::Entity &oneEyeEntity = charactherSpawns.getEntitiesByName(
			"Blue_Dragon")[0].get();
	ldtk::Entity &EnemyEntity =
			charactherSpawns.getEntitiesByName("Napper_Bat")[0].get();
	//---------------------------------------------------//

	backgroundMusic = ResourceLoader::getResourceLoader()->getMusics(
			"musicFilmore");
	GameMusic(backgroundMusic);

	player = new Angel();
	charactersVector.push_back(player);

	sf::Vector2f enemyPosition(static_cast<float>(oneEyeEntity.getPosition().x),
			static_cast<float>(oneEyeEntity.getPosition().y));
	charactersVector.push_back(new OneEye(enemyPosition));

	enemyPosition.x = static_cast<float>(EnemyEntity.getPosition().x);
	enemyPosition.y = static_cast<float>(EnemyEntity.getPosition().y);
	charactersVector.push_back(new Enemy(enemyPosition));
	enemyPosition.x += 30;
	charactersVector.push_back(new NapperBat(enemyPosition));

	camera.setSize( { 256, 144 });
	camera.zoom(1.6f);
	camera.setCenter(player->sprite.getPosition());
	cameraBounds.left = 0;
	cameraBounds.top = 0;
	cameraBounds.width = static_cast<float>(ldtkLevel0.size.x);
	cameraBounds.height = static_cast<float>(ldtkLevel0.size.y);

	// Setting up the fonts and text
	//todo[Carregar fonte pelo ResourceLoader]
	textFont.loadFromFile("Assets/Font/Poppins.ttf");
	lifeText.setFont(textFont);
	lifeText.setFillColor(sf::Color::Red);
	lifeText.setCharacterSize(8);
}

void Game::run() {
	while (window->isOpen()) {
		sf::Event event;

		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
		}

		float deltaTime = time.restart().asSeconds();

		Update(deltaTime);
		window->clear();
		Render(window);
		window->display();
	}

}

void Game::Update(float &deltaTime) {

	for (Character* personagem : charactersVector) {
			personagem->UpdateDeltaTime(deltaTime);
		    }

	for (std::list<Character*>::iterator it = charactersVector.begin();
			it != charactersVector.end(); ++it) {
		Character *personagem = *it;
		if(personagem->ativo == false){
			delete(*it);
			charactersVector.erase(it);
		}
	}

	//todo[estabelecer colisões]
	// Get the Coliisor Bounds of all characters
	/*auto playerCollider = GetPlayerCollider(player->sprite);
	auto oneEyeCollider = GetEnemyCollider(charactersVector[1]->sprite);
	auto EnemyCollider = GetEnemyCollider(charactersVector[2]->sprite);

	// Testing the collision with a enemy and showing the damage given
	if (playerCollider.intersects(oneEyeCollider)
			and player->cooldownCount.getElapsedTime().asSeconds()
					>= player->cooldownTime) {
		player->vidas -= 1;

		char str[5];
		if (player->vidas >= 0) {
			sprintf(str, "Vidas: \t%d", player->vidas);
			lifeText.setString(str);
		}

	}

	if (playerCollider.intersects(EnemyCollider)
			and player->cooldownCount.getElapsedTime().asSeconds()
					>= player->cooldownTime) {
		player->vidas -= 3;

		char str[5];
		if (player->vidas >= 0) {
			sprintf(str, "Vidas: \t%d", player->vidas);
			lifeText.setString(str);
		}

	}
*/
// Code for adding Collision between the player and the map
//	for (auto &rect : colliders) {
//		sf::FloatRect intersect;
//		if (playerCollider.intersects(rect, intersect)) {
//			if (intersect.width < intersect.height) {
//				if (playerCollider.left < intersect.left)
//					anjinho->sprite.move(-intersect.width, 0);
//				else
//					anjinho->sprite.move(intersect.width, 0);
//			} else {
//				if (playerCollider.top < intersect.top)
//					anjinho->sprite.move(0, -intersect.height);
//				else
//					anjinho->sprite.move(0, intersect.height);
//			}
//		}
//	}

	moveCamera();
}

void Game::moveCamera() {
	sf::Vector2f movment;// = (anjinho->sprite.getPosition() - camera.getCenter())/5.f;
	int offset = 10;

	//Controla o movimento ao longo de x.
	if ((player->sprite.getPosition().x + offset > camera.getSize().x / 2)
			&& (player->sprite.getPosition().x - offset
					< cameraBounds.width - camera.getSize().x / 2))
		movment.x = (player->sprite.getPosition().x - camera.getCenter().x)
				/ 5.f;

	//Controla o movimento ao longo de y.
	if ((player->sprite.getPosition().y + offset > camera.getSize().y / 2)
			&& (player->sprite.getPosition().y - offset
					< cameraBounds.height - camera.getSize().y / 2))
		movment.y = (player->sprite.getPosition().y - camera.getCenter().y)
				/ 5.f;

	//Versï¿½o do movimento sem controle de bordas
	//movment = (anjinho->sprite.getPosition()- camera.getCenter())/ 5.f;
	camera.move(movment);
}

void Game::Render(sf::RenderTarget *target) {
	target->setView(camera);

	// Drawing the Ground Layer
	target->draw(GameMap.GetLayer("Ground"));
	target->draw(GameMap.GetLayer("Tree"));

	// Drawing the Obstacles Layer
	target->draw(GameMap.GetLayer("Obstacles"));

	// Drawing Characters // Drawing the bullets
	for (auto it = charactersVector.rbegin(); it != charactersVector.rend();
			++it) {
		Character *personagem = *it;
		personagem->Draw(target);
	}
	// Drawing the player life
	lifeText.setPosition(camera.getCenter().x - 85, camera.getCenter().y - 50);
	target->draw(lifeText);

	///sf::Vertex line[] = { sf::Vertex(sf::Vector2f(0, 0)), sf::Vertex(
	//sf::Vector2f(anjinho->animatedSprite.getPosition())) };
	//target->draw(line, 2, sf::Lines);
}
void Game::close() {
	this->backgroundMusic->stop();
}

Game::~Game() {
	for (Character *personagem : charactersVector) {
		delete personagem;
	}
}
