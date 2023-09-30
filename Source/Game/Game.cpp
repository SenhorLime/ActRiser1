
#include "Game.hpp"
#include "Collision.hpp"

#include <iostream>
#include <cstddef> //For nullptr_t

Game *Game::instance = nullptr;
;

Game::Game() {
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

void Game::GameMusic(sf::Music &backgroundMusic) {
	//backgroundMusic.openFromFile("Assets/Music/Monster.ogg");
	backgroundMusic.play();
	backgroundMusic.setVolume(50);
	backgroundMusic.setLoop(true);
}

void Game::Init() {
	// Get the game World from the project
	//Alisson Esteve aqui.
	//auto &world = ldtk_proj.getWorld();
	// Get the level from the project
	auto &ldtkLevel0 = this->GameMap.world->getLevel("Level_0");

	// Load the TileMap from the level
	GameMap.Load(ldtkLevel0);

	// Get the layer of Entities
//	auto &worldCollissions = ldtkLevel0.getLayer("Map_Collissions");
	auto &charactherSpawns = ldtkLevel0.getLayer("Spanws");

	// Get the Collider shapes and store then in a std::vector
//	for (ldtk::Entity &col : worldCollissions.getEntitiesByName("Map_Collider")) {
//		colliders.emplace_back((float) col.getPosition().x,
//				(float) col.getPosition().y, (float) col.getSize().x,
//				(float) col.getSize().y);
//	}

	// Get the map Entities for setting the characters spawn points
//	ldtk::Entity &playerEntity =
//			charactherSpawns.getEntitiesByName("Player")[0].get();
	ldtk::Entity &oneEyeEntity =
			charactherSpawns.getEntitiesByName("Blue_Dragon")[0].get();
	ldtk::Entity &nebulonEntity =
			charactherSpawns.getEntitiesByName("Napper_Bat")[0].get();

	backgroundMusic.openFromFile("Assets/Music/15-Birth-of-the-People.ogg");
	GameMusic(backgroundMusic);

//	SetPlayerPosition(playerEntity);
	SetOneEyePostion(oneEyeEntity);
	SetNebulonPosition(nebulonEntity);

	anjinho.sprite.setPosition(200, 200);
	camera.setSize( { 256, 144 });
	camera.zoom(0.7f);
	camera.setCenter(anjinho.sprite.getPosition());
	cameraBounds.left = 0;
	cameraBounds.top = 0;
	cameraBounds.width = static_cast<float>(ldtkLevel0.size.x);
	cameraBounds.height = static_cast<float>(ldtkLevel0.size.y);

	// Setting up the fonts and text
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

void Game::SetPlayerPosition(ldtk::Entity &playerEntity) {
	anjinho.sprite.setPosition(static_cast<float>(playerEntity.getPosition().x),
			static_cast<float>(playerEntity.getPosition().y));
}

void Game::SetOneEyePostion(ldtk::Entity &oneEyeEntity) {
	oneEye.sprite.setPosition(static_cast<float>(oneEyeEntity.getPosition().x),
			static_cast<float>(oneEyeEntity.getPosition().y));
}

void Game::SetNebulonPosition(ldtk::Entity &nebulonEntity) {
	nebulon.sprite.setPosition(
			static_cast<float>(nebulonEntity.getPosition().x),
			static_cast<float>(nebulonEntity.getPosition().y));
}

void Game::Update(float &deltaTime) {
	// Updating the player movement
	anjinho.UpdateDeltaTime(deltaTime);
	anjinho.ShootArrow(anjinho.GetPostion());
	anjinho.MoveCharacter();

	// Updating the Enemies movement
	oneEye.UpdateDeltaTime(deltaTime);
	oneEye.MoveCharacter();
	nebulon.UpdateDeltaTime(deltaTime);
	nebulon.MoveCharacter();

	// Get the Coliisor Bounds of all characters
	auto playerCollider = GetPlayerCollider(anjinho.sprite);
	auto oneEyeCollider = GetEnemyCollider(oneEye.sprite);
	auto nebulonCollider = GetEnemyCollider(nebulon.sprite);

	// Testing the collision with a enemy and showing the damage given
	if (playerCollider.intersects(oneEyeCollider)
			and anjinho.cooldownCount.getElapsedTime().asSeconds()
					>= anjinho.cooldownTime) {
		anjinho.vidas -= 1;

		char str[5];
		if (anjinho.vidas >= 0) {
			sprintf(str, "Vidas: \t%d", anjinho.vidas);
			lifeText.setString(str);
		}

		//oneEye.cooldownCount.restart();
	}

	if (playerCollider.intersects(nebulonCollider)
			and anjinho.cooldownCount.getElapsedTime().asSeconds()
					>= anjinho.cooldownTime) {
		anjinho.vidas -= 3;

		char str[5];
		if (anjinho.vidas >= 0) {
			sprintf(str, "Vidas: \t%d", anjinho.vidas);
			lifeText.setString(str);
		}

		//nebulon.cooldownCount.restart();
	}

// Code for adding Collision between the player and the map
//	for (auto &rect : colliders) {
//		sf::FloatRect intersect;
//		if (playerCollider.intersects(rect, intersect)) {
//			if (intersect.width < intersect.height) {
//				if (playerCollider.left < intersect.left)
//					anjinho.sprite.move(-intersect.width, 0);
//				else
//					anjinho.sprite.move(intersect.width, 0);
//			} else {
//				if (playerCollider.top < intersect.top)
//					anjinho.sprite.move(0, -intersect.height);
//				else
//					anjinho.sprite.move(0, intersect.height);
//			}
//		}
//	}

	moveCamera();
}

void Game::moveCamera() {
	sf::Vector2f movment;// = (anjinho.sprite.getPosition() - camera.getCenter())/5.f;
	int offset = 10;

	//Controla o movimento ao longo de x.
	if ((anjinho.sprite.getPosition().x + offset > camera.getSize().x / 2) &&
	   (anjinho.sprite.getPosition().x - offset < cameraBounds.width - camera.getSize().x/2))
		movment.x = (anjinho.sprite.getPosition().x - camera.getCenter().x)/ 5.f;

	//Controla o movimento ao longo de y.
	if ((anjinho.sprite.getPosition().y + offset > camera.getSize().y / 2) &&
	   (anjinho.sprite.getPosition().y - offset < cameraBounds.height - camera.getSize().y/2))
		movment.y = (anjinho.sprite.getPosition().y - camera.getCenter().y)/ 5.f;

	//Vers�o do movimento sem controle de bordas
	//movment = (anjinho.sprite.getPosition()- camera.getCenter())/ 5.f;
	camera.move(movment);
}

void Game::Render(sf::RenderTarget *target) {
	target->setView(camera);

	// Drawing the Ground Layer
	target->draw(GameMap.GetLayer("Ground"));
	target->draw(GameMap.GetLayer("Tree"));

	// Drawing the Obstacles Layer
	target->draw(GameMap.GetLayer("Obstacles"));


	//Drawing the player
	anjinho.draw(target);

	// Drawing the Enemies
	oneEye.draw(target);
	nebulon.draw(target);

	// Drawing the player life
	lifeText.setPosition(camera.getCenter().x - 85, camera.getCenter().y - 50);
	target->draw(lifeText);

	// Drawing the bullets
	for (auto &arrow : anjinho.arrows) {
		arrow.Update();
		target->draw(arrow.texture);
	}

	sf::Vertex line[] = { sf::Vertex(sf::Vector2f(0, 0)), sf::Vertex(
			sf::Vector2f(anjinho.GetPostion())) };

	target->draw(line, 2, sf::Lines);
}
void Game::close() {
	this->backgroundMusic.stop();
}


Game::~Game(){}
