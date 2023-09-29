#include "Source/Game/Game.hpp"
//#include "Source/Music/Music.hpp"

#include <string>
#include <iostream>


int main() {

	// Initializing the game from the LDtk project data
	Game  * ActRaiser = Game::getGame();
	ActRaiser->Init();
	ActRaiser->run();
	ActRaiser->close();

}
