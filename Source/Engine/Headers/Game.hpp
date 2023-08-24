#ifndef ACTRISE1_GAME_HPP
#define ACTRISE1_GAME_HPP

#include "Window.hpp"

class Game {
public:
  void Start();

private:
  bool IsQuiting();

  void GameLoop();

  void ShowSplashScreen();
  void ShowMenu();

  enum GameState {
      Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Dialog, Quiting
  };

private:
  GameState gameState;
  Window EngineWindow;
};


#endif //ACTRISE1_GAME_HPP
