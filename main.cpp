#include "Source/Game/Game.hpp"
#include "Source/Music/Music.hpp"

#include <LDtkLoader/Project.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

int main() {
	ldtk::Project project;
	std::string ldtk_filename = "Assets/Maps/GameMap.ldtk";
	try {
		project.loadFromFile(ldtk_filename);
		std::cout << "\nLDtk World \"" << project.getFilePath()
				<< "\" was loaded successfully." << std::endl;
	} catch (std::exception &ex) {
		std::cerr << ex.what() << std::endl;
		return 1;
	}

	// Initializing the game from the LDtk project data
	Game ActRaiser;
	ActRaiser.Init(project);

	// Creating the Game Window and setting visual configuration
	sf::RenderWindow window(sf::VideoMode(1280, 720), "ActRaiser77");
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(60);

	// Creating a Clock variable for updating the movement of the player
	sf::Clock time;

	sf::Music backgroundMusic;
	GameMusic(backgroundMusic);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		float deltaTime = time.restart().asSeconds();

		ActRaiser.Update(deltaTime);
		window.clear();
		ActRaiser.Render(window);
		window.display();
	}
}
