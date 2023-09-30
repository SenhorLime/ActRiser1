#pragma once


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
#include "../Characters/Angel/Angel.hpp"
#include "../Characters/Enemies/OneEye.hpp"
#include "../Characters/Enemies/Nebulon.hpp"

class Game {
private:
	TileMap GameMap;

	Angel anjinho;
	OneEye oneEye;
	Nebulon nebulon;

	sf::View camera;

	sf::Font textFont;
	sf::Text lifeText;

	std::vector<sf::FloatRect> colliders;
	bool showCollider = false;

	static Game *instance;

	sf::RenderWindow * window;
	sf::Clock time;

	sf::Music backgroundMusic;

public:
	sf::FloatRect cameraBounds;
	static Game * getGame();

	void Init();

	void run();

	void Update(float &deltaTime);

	void Render(sf::RenderTarget * target);

	void close();

	virtual ~Game();
	const sf::RenderWindow * getWindow() const;


private:
	Game();
	void GameMusic(sf::Music &backgroundMusic) ;

	void moveCamera() ;

	void SetPlayerPosition(ldtk::Entity &playerEntity);

	void SetOneEyePostion(ldtk::Entity &oneEyeEntity);

	void SetNebulonPosition(ldtk::Entity &nebulonEntity);
};
