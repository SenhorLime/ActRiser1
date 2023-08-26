#include "Headers/SplashScreen.hpp"

void SplashScreen::Show(Window &EngineWindow) {
  LoadSprites("../Assets/SplashScreen/SplashScreen.png");

  EngineWindow.mainWindow.clear();
  EngineWindow.mainWindow.draw(sprite);
  EngineWindow.mainWindow.display();
}

void SplashScreen::HandleEvents(Window &EngineWindow, sf::Event &event) {
  while (EngineWindow.mainWindow.isOpen()) {
    while (EngineWindow.mainWindow.pollEvent(event)) {
      if (event.key.code == sf::Keyboard::Escape) { return; }
    }
  }
}



