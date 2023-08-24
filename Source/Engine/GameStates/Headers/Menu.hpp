#ifndef ACTRISE1_MENU_HPP
#define ACTRISE1_MENU_HPP

#include "../../Headers/Window.hpp"

#include <list>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Menu {
public:
  enum MenuResult {
      Nothing, Exit, Play
  };

  class MenuItem {
  public:
    sf::Rect<int> rect;
    MenuResult action;
  };

  MenuResult Show(Window &EngineWindow);

private:
  MenuResult GetMenuResponse(Window &EngineWindow);

  MenuResult HandleClick(sf::Vector2i mouseInput);

  void LoadSprites();

  void SetButtons();

  std::list<MenuItem> menuItems;
  sf::Texture menuTexture;
  sf::Sprite menuSprite;
};


#endif //ACTRISE1_MENU_HPP
