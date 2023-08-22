#include "Headers/Game.hpp"

Game::Game() {}

void Game::Start() { window.Render(); }

/*void Game::SetGameState() {
	switch (gameState.GameStates) {
		case StateMachine::SplashScreen:
			gameState.ShowSplashScreen(window);
	}
}*/

