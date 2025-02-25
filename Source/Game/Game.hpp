
#pragma once

#include <list>
#include <vector>

#include <LDtkLoader/Project.hpp>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Music.hpp>

#include "../GameMap/TileMap.hpp"

#include "../Characters/Enemy.hpp"
#include "../Characters/Angel/Includes/Angel.hpp"
#include "../Characters/Enemies/Includes/NapperBat.hpp"
#include "../Characters/Enemies/Includes/BlueDragon.hpp"
#include "../Characters/Enemies/Includes/RedDemon.hpp"


class Game {
private:
  TileMap GameMap;

  Angel *player;

  sf::View camera;

  sf::Font textFont;
  sf::Text lifeText;

  std::vector<sf::FloatRect> colliders;
  bool showCollider = false;

  static Game *instance;

  sf::RenderWindow *window;
  sf::Clock time;

  sf::Music *backgroundMusic;

public:
  sf::FloatRect cameraBounds;

  std::list<Character *> charactersVector;
  std::list<Enemy *> enemyVector;
  std::list<Arrow *> arrowVector;

  static Game *getGame();

  void Init();

  void run();

  void Update(float &deltaTime);

  void Render(sf::RenderTarget *target);

  void close();

  virtual ~Game();


private:
  Game();

  void GameMusic(sf::Music *backgroundMusic);

  void carregaAssets();

  void moveCamera();

};
