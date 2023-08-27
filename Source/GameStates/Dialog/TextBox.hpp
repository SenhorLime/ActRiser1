#ifndef ACTRISE1_TEXTBOX_HPP
#define ACTRISE1_TEXTBOX_HPP

#include "../../GameEngine/Window/Window.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

class TextBox {
public:
  void RenderDialog(Window &EngineWindow);

private:
  void LoadFont(std::string fontPath);

  void setText();

private:
  sf::Font font;
  sf::Text dialog;
};


#endif //ACTRISE1_TEXTBOX_HPP
