#pragma once


#include <LDtkLoader/Project.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

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
	sf::FloatRect cameraBounds;
	sf::Font textFont;
	sf::Text lifeText;

	std::vector<sf::FloatRect> colliders;
	bool showCollider = false;
public:
	void Init(const ldtk::Project &ldtk_proj);

	void Update(float &deltaTime);

	void Render(sf::RenderTarget &target);

private:
	void SetPlayerPosition(ldtk::Entity &playerEntity);

	void SetOneEyePostion(ldtk::Entity &oneEyeEntity);

	void SetNebulonPosition(ldtk::Entity &nebulonEntity);
};
