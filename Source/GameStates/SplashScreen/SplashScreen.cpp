#include "SplashScreen.hpp"

void InitialStatesRender::Show(Window &EngineWindow) {
  InitialStatesRender::LoadSprites("../Assets/SplashScreen/SplashScreen.png");

  EngineWindow.mainWindow.clear();
  EngineWindow.mainWindow.draw(sprite);
  EngineWindow.mainWindow.display();
}

void InitialStatesRender::HandleEvents(Window &EngineWindow, sf::Event &event) {
  while (EngineWindow.mainWindow.isOpen()) {
    while (EngineWindow.mainWindow.pollEvent(event)) {
      if (event.key.code == sf::Keyboard::Escape) { return; }
    }
  }
}



