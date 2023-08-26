#ifndef ACTRISE1_MENU_HPP
#define ACTRISE1_MENU_HPP

#include "../../Engine/Headers/Window.hpp"
#include "InitialStatesRender.hpp"

#include <list>


class Menu : public InitialStatesRender {
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

  void SetButtons();

private:
  std::list<MenuItem> menuItems;
};


#endif //ACTRISE1_MENU_HPP
