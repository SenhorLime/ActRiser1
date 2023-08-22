#ifndef ACTRISE1_GAME_HPP
#define ACTRISE1_GAME_HPP

#include "Window.hpp"
//#include "StateMachine.hpp"

class Game {
public:
	Game();

	void Start();
private:
	//void SetGameState();

	Window window;
	//StateMachine gameState;
};


#endif //ACTRISE1_GAME_HPP
