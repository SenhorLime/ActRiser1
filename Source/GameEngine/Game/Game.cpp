#include "Game.hpp"
#include "../../GameStates/Menu/Menu.hpp"
#include "../../GameStates/Dialog/TextBox.hpp"
#include "../../GameStates/SplashScreen/SplashScreen.hpp"

void Game::Start() {
  if (gameState != Uninitialized) { return; }

  gameState = Game::Dialog;

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
      case Game::Dialog:
        ShowDialog();
        break;
      case Game::Playing:
        EngineWindow.mainWindow.clear(sf::Color::White);
        EngineWindow.mainWindow.display();

        if (EngineWindow.HandleEvents() == sf::Event::Closed) {
          gameState = Game::Quiting;
        }
        break;
    }
  }
}

void Game::ShowDialog() {
  TextBox textBox;
  textBox.RenderDialog(EngineWindow);
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
      gameState = Game::Dialog;
      break;
  }
}