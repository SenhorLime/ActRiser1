#include "Menu.hpp"

void Menu::SetButtons() {
  MenuItem playButton;
  playButton.rect.top = 145;
  playButton.rect.left = 0;
  playButton.rect.height = 380;
  playButton.rect.width = 1023;
  playButton.action = Play;

  MenuItem exitButton;
  exitButton.rect.top = 383;
  exitButton.rect.left = 0;
  exitButton.rect.height = 560;
  exitButton.rect.width = 1023;
  exitButton.action = Exit;

  menuItems.push_back(playButton);
  menuItems.push_back(exitButton);

}

Menu::MenuResult Menu::Show(Window &EngineWindow) {
  InitialStatesRender::LoadSprites("../Assets/Menu/mainmenu.png");
  SetButtons();

  EngineWindow.mainWindow.clear();
  EngineWindow.mainWindow.draw(sprite);
  EngineWindow.mainWindow.display();

  return GetMenuResponse(EngineWindow);
}

Menu::MenuResult Menu::GetMenuResponse(Window &EngineWindow) {
  sf::Event event;

  while (EngineWindow.mainWindow.isOpen()) {
    while (EngineWindow.mainWindow.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::MouseButtonPressed:
          return HandleClick({event.mouseButton.x, event.mouseButton.y});
      }
    }
  }
  return Exit;
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

