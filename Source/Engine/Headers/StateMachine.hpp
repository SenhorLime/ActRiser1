#ifndef ACTRISE1_STATEMACHINE_HPP
#define ACTRISE1_STATEMACHINE_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Window.hpp"

class StateMachine {
public:
	StateMachine();

	enum States {
		SplashScreen, GameMenu, Dialog, Paused, Playing
	};

	States GameStates;

public:
	void UpdateState();

	void ShowSplashScreen(Window &window);

	void ShowGameMenu();

	void ShowPaused();

	void ShowDialog();

	void ShowPlaying();

};


#endif //ACTRISE1_STATEMACHINE_HPP
