#include <SFML/Audio/Music.hpp>

void GameMusic(sf::Music &backgroundMusic) {
	//backgroundMusic.openFromFile("Assets/Music/Monster.ogg");
	backgroundMusic.openFromFile("Assets/Music/15-Birth-of-the-People.ogg");

	backgroundMusic.play();
	backgroundMusic.setVolume(50);
	backgroundMusic.setLoop(true);
}
