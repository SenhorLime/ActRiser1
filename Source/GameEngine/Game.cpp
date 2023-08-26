#include "Headers/Game.hpp"
#include "../GameStates/Headers/SplashScreen.hpp"
#include "../GameStates/Headers/Menu.hpp"

void Game::Start() {
  if (gameState != Uninitialized) { return; }

  gameState = Game::Playing;

  while (!IsQuiting()) {
    GameLoop();
  }

  EngineWindow.mainWindow.close();
}

bool Game::IsQuiting() {
  if (gameState == Game::Quiting) {
    return true;
  } else {
    return false;
  }
}

void Game::GameLoop() {
  sf::Event event;

  while (EngineWindow.mainWindow.isOpen()) {
    EngineWindow.HandleEvents();

    switch (gameState) {
      case Game::ShowingSplash:
        ShowSplashScreen();
        break;
      case Game::ShowingMenu:
        ShowMenu();
        break;
      case Game::Playing:
        EngineWindow.mainWindow.clear();
        EngineWindow.mainWindow.display();

        if (EngineWindow.HandleEvents() == sf::Event::Closed) {
          gameState = Game::Quiting;
        }
        break;
    }
  }
}

void Game::ShowSplashScreen() {
  sf::Event event;
  SplashScreen splash;

  splash.Show(EngineWindow);
  splash.HandleEvents(EngineWindow, event);

  gameState = ShowingMenu;
}

void Game::ShowMenu() {
  Menu mainMenu;

  Menu::MenuResult result = mainMenu.Show(EngineWindow);

  switch (result) {
    case Menu::Exit:
      gameState = Game::Quiting;
      break;
    case Menu::Play:
      gameState = Game::Playing;
      break;
  }
}