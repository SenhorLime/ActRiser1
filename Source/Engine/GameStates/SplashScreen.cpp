#include "Headers/SplashScreen.hpp"

sf::Sprite SplashScreen::LoadSprites() {
  sf::Texture splashTexture;
  sf::Sprite splashSprite;

  splashTexture.loadFromFile("../Assets/SplashScreen/SplashScreen.png");
  splashSprite.setTexture(splashTexture);

  return splashSprite;
}

void SplashScreen::Show(Window &EngineWindow) {
  EngineWindow.mainWindow.draw(LoadSprites());
  EngineWindow.mainWindow.display();

  sf::Event event;
  while (true) {
    while (EngineWindow.mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        return;
      }
    }
  }
}



