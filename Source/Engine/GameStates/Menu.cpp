#include "Headers/Menu.hpp"

#include <SFML/Graphics/Texture.hpp>

void Menu::LoadSprites() {
  menuTexture.loadFromFile("../Assets/SplashScreen/mainmenu.png");
  menuSprite.setTexture(menuTexture);
}

void Menu::SetButtons() {
  MenuItem playButton;
  playButton.rect.top = 145;
  playButton.rect.height = 380;
  playButton.rect.left = 0;
  playButton.rect.width = 1023;
  playButton.action = Play;

  MenuItem exitButton;
  exitButton.rect.left = 0;
  exitButton.rect.width = 1023;
  exitButton.rect.top = 383;
  exitButton.rect.height = 560;
  exitButton.action = Exit;

  menuItems.push_back(playButton);
  menuItems.push_back(exitButton);

}

Menu::MenuResult Menu::Show(Window &EngineWindow) {
  LoadSprites();
  SetButtons();

  EngineWindow.mainWindow.clear();
  EngineWindow.mainWindow.draw(menuSprite);
  EngineWindow.mainWindow.display();

  return GetMenuResponse(EngineWindow);
}

Menu::MenuResult Menu::HandleClick(sf::Vector2i mouseInput) {
  std::list<MenuItem>::iterator it;

  for (it = menuItems.begin(); it != menuItems.end(); it++) {
    sf::Rect<int> menuItemRect = (*it).rect;

    if ((menuItemRect.height > mouseInput.y && menuItemRect.top < mouseInput.y)
        && (menuItemRect.left < mouseInput.x && menuItemRect.width > mouseInput.x)) {
      return (*it).action;
    }
  }

  return Nothing;
}

Menu::MenuResult Menu::GetMenuResponse(Window &EngineWindow) {
  sf::Event event;

  while (true) {
    while (EngineWindow.mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::MouseButtonPressed) {
        return HandleClick({event.mouseButton.x, event.mouseButton.y});
      }

      if (event.type == sf::Event::Closed) { return Exit; }
    }
  }
}