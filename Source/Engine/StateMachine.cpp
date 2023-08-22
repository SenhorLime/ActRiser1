#include "Headers/StateMachine.hpp"
#include "Headers/Window.hpp"

StateMachine::StateMachine() {}

void StateMachine::ShowSplashScreen(Window &window) {
	sf::Texture texture;
	sf::Sprite sprite;

	if(!texture.loadFromFile("image.jpg")) {
		sprite.setTexture(texture);
	}

	window.Draw(sprite);
}