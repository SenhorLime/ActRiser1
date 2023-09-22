#include <SFML/Audio/Music.hpp>

void GameMusic(sf::Music &backgroundMusic) {
	backgroundMusic.openFromFile("Assets/Music/Monster.ogg");

	backgroundMusic.play();
	backgroundMusic.setVolume(50);
	backgroundMusic.setLoop(true);
}
