#include "Game.hpp"
#include "Collision.hpp"
#include "./ResourceLoader.hpp"

#include <iostream>
#include <typeinfo>
#include <cstddef> //For nullptr_t
#include <random>

Game *Game::instance = nullptr;;

Game::Game() :
    player(nullptr) {
    window = new sf::RenderWindow();
    window->create(sf::VideoMode(1280, 720), "ActRaiser77");
    window->setMouseCursorVisible(false);
    window->setFramerateLimit(60);

    sf::Music backgroundMusic;

}

Game *Game::getGame() {
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
    //sf::Color cor(120, 144, 0);
    image.createMaskFromColor(sf::Color(120, 144, 0));
    sf::Texture _textura;
    _textura.loadFromImage(image);
    _textura.setSmooth(true);
    resources->addTextura("Angel", _textura);

    if (!image.loadFromFile("Assets/Enemy/Enemy.png")) {
        std::cerr << "Erro carregando imagem Enemy.png" << std::endl;
    }
    image.createMaskFromColor(sf::Color(0, 64, 128));
    _textura.loadFromImage(image);
    _textura.setSmooth(true);
    resources->addTextura("Enemy", _textura);

    if (!image.loadFromFile("Assets/Characters/vilages.png")) {
        std::cerr << "Erro carregando imagem vilages.png" << std::endl;
    }
    image.createMaskFromColor(sf::Color(0, 102, 0));
    _textura.loadFromImage(image);
    _textura.setSmooth(true);
    resources->addTextura("Vilages", _textura);

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
    auto &charactherSpawns = ldtkLevel0.getLayer("Monster_Lairs");

    ldtk::Entity &BlueDragonLair = charactherSpawns.getEntitiesByName("Blue_Dragon")[0].get();
    ldtk::Entity &NapperBatLair = charactherSpawns.getEntitiesByName("Napper_Bat")[0].get();
    //---------------------------------------------------//

    backgroundMusic = ResourceLoader::getResourceLoader()->getMusics(
        "musicFilmore");
    GameMusic(backgroundMusic);

    player = new Angel();
    charactersVector.push_back(player);

    sf::Vector2f enemyPosition(static_cast<float>(BlueDragonLair.getPosition().x),
                               static_cast<float>(BlueDragonLair.getPosition().y));

    charactersVector.push_back(new BlueDragon(enemyPosition));
    enemyVector.push_back(dynamic_cast<Enemy *>(charactersVector.back()));

    enemyPosition.x = static_cast<float>(NapperBatLair.getPosition().x);
    enemyPosition.y = static_cast<float>(NapperBatLair.getPosition().y);
    charactersVector.push_back(new Enemy(enemyPosition));
    enemyVector.push_back(dynamic_cast<Enemy *>(charactersVector.back()));

    charactersVector.push_back(new RedDemon(enemyPosition));
    enemyVector.push_back(dynamic_cast<Enemy *>(charactersVector.back()));

    enemyPosition.x += 30;

    charactersVector.push_back(new NapperBat(enemyPosition));
    enemyVector.push_back(dynamic_cast<Enemy *>(charactersVector.back()));

    camera.setSize({256, 144});
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
    static long i = 0;
//    std::cout << "Iteração: " << i++ << std::endl;
    for (Character *personagem: charactersVector) {
        personagem->UpdateDeltaTime(deltaTime);
    }

    //todo[estabelecer colisões]
    for (std::list<Enemy *>::iterator itEnemy = enemyVector.begin();
         itEnemy != enemyVector.end(); ++itEnemy) {
        Enemy *enemy = *itEnemy;
        if (!enemy->ativo) {
            enemyVector.erase(itEnemy);
            continue;
        }

        if (enemy->getMyBounds().intersects(player->getMyBounds()) and player->CanTakeDamage()) {
            player->takeDamage(enemy->GetDamage());
            std::cout << typeid(*player).name() << " colidiu com " << typeid(*enemy).name() << std::endl;
            continue;
        }

        for (std::list<Arrow *>::iterator itArrow = arrowVector.begin();
             itArrow != arrowVector.end(); ++itArrow) {
            Arrow *arrow = *itArrow;
            if (!arrow->ativo) {
                arrowVector.erase(itArrow);
                continue;
            }
            if (arrow->getMyBounds().intersects(enemy->getMyBounds())) {
                arrow->ativo = false;
                arrowVector.erase(itArrow);
                enemy->takeDamage(1);
                std::cout << typeid(*arrow).name() << " colidiu com " << typeid(*enemy).name() << std::endl;
            }

        }

    }

    for (std::list<Character *>::iterator it = charactersVector.begin();
         it != charactersVector.end(); ++it) {
        Character *personagem = *it;
        if (!personagem->ativo) {
            delete (*it);
            charactersVector.erase(it);
        }
    }
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
    sf::Vector2f movement;// = (anjinho->sprite.getPosition() - camera.getCenter())/5.f;
    int offset = 10;

    //Controla o movimento ao longo de x.
    if ((player->sprite.getPosition().x + offset > camera.getSize().x / 2)
        && (player->sprite.getPosition().x - offset
            < cameraBounds.width - camera.getSize().x / 2))
        movement.x = (player->sprite.getPosition().x - camera.getCenter().x)
                     / 5.f;

    //Controla o movimento ao longo de y.
    if ((player->sprite.getPosition().y + offset > camera.getSize().y / 2)
        && (player->sprite.getPosition().y - offset
            < cameraBounds.height - camera.getSize().y / 2))
        movement.y = (player->sprite.getPosition().y - camera.getCenter().y)
                     / 5.f;

    camera.move(movement);
}

void Game::Render(sf::RenderTarget *target) {
    target->setView(camera);

    // Drawing the Ground Layer
    target->draw(GameMap.GetLayer("Ground"));
    target->draw(GameMap.GetLayer("Tree"));

    // Drawing the Obstacles Layer
    target->draw(GameMap.GetLayer("Obstacles"));

    // Drawing Characters // Drawing the bullets
//	for (auto it = charactersVector.rbegin(); it != charactersVector.rend();
//			++it) {
//		Character *personagem = *it;
//		personagem->Draw(target);
//	}

    for (Character *personagem: charactersVector) {
        if (personagem->ativo)
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
    for (Character *personagem: charactersVector) {
        delete personagem;
    }
}
