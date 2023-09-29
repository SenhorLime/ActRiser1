#include "Game.hpp"
#include "Collision.hpp"

#include <iostream>
#include <cstddef> //For nullptr_t

Game* Game::instance= nullptr;;

Game::Game(){}

Game *Game::getGame(){
	    if(instance==nullptr){
	    	instance = new Game();
	    }
	    return instance;
	}


void Game::Init(const ldtk::Project &ldtk_proj) {
	// Get the game World from the project
	//Alisson Esteve aqui.
	auto &world = ldtk_proj.getWorld();
	// Get the level from the project
	auto &ldtkLevel0 = world.getLevel("Level_0");

	// Load the TileMap from the level
	TileMap::path = ldtk_proj.getFilePath().directory();
	GameMap.Load(ldtkLevel0);

	// Get the layer of Entities
	auto &worldCollissions = ldtkLevel0.getLayer("Map_Collissions");
	auto &charactherSpawns = ldtkLevel0.getLayer("Spawns");

	// Get the Collider shapes and store then in a std::vector
	for (ldtk::Entity &col : worldCollissions.getEntitiesByName("Map_Collider")) {
		colliders.emplace_back((float) col.getPosition().x,
				(float) col.getPosition().y, (float) col.getSize().x,
				(float) col.getSize().y);
	}

	// Get the map Entities for setting the characters spawn points
	ldtk::Entity &playerEntity =
			charactherSpawns.getEntitiesByName("Player")[0].get();
	ldtk::Entity &oneEyeEntity =
			charactherSpawns.getEntitiesByName("OneEye")[0].get();
	ldtk::Entity &nebulonEntity =
			charactherSpawns.getEntitiesByName("Nebulon")[0].get();

	SetPlayerPosition(playerEntity);
	SetOneEyePostion(oneEyeEntity);
	SetNebulonPosition(nebulonEntity);

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
	if (playerCollider.intersects(oneEyeCollider) and anjinho.cooldownCount.getElapsedTime().asSeconds() >= anjinho.cooldownTime) {
		anjinho.vidas -= 1;

		char str[5];
		if (anjinho.vidas >= 0) {
			sprintf(str, "Vidas: \t%d", anjinho.vidas);
			lifeText.setString(str);
		}

		//oneEye.cooldownCount.restart();
	}

	if (playerCollider.intersects(nebulonCollider) and anjinho.cooldownCount.getElapsedTime().asSeconds() >= anjinho.cooldownTime) {
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

	camera.move((anjinho.sprite.getPosition() - camera.getCenter()) / 5.f);
}

void Game::Render(sf::RenderTarget &target) {
	target.setView(camera);

	// Drawing the Ground Layer
	target.draw(GameMap.GetLayer("Ground"));

	// Drawing the Obstacles Layer
	target.draw(GameMap.GetLayer("Obstacles"));

	//Drawing the player
	target.draw(anjinho.sprite);

	// Drawing the Enemies
	target.draw(oneEye.sprite);
	target.draw(nebulon.sprite);

	// Drawing the player life
	lifeText.setPosition(camera.getCenter().x - 85, camera.getCenter().y - 50);
	target.draw(lifeText);

	// Drawing the bullets
	for (auto &arrow : anjinho.arrows) {
		arrow.Update();
		target.draw(arrow.texture);
	}

}

 Game::~Game(){
	std::cout<< "Game Destruido!" <<std::endl;
	delete(Game::getGame());

}
