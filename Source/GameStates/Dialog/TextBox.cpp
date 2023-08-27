#include "TextBox.hpp"

void TextBox::LoadFont(std::string fontPath) { font.loadFromFile(fontPath); }

void TextBox::setText() {
  LoadFont("../Assets/TextBox/Cabin.ttf");

  dialog.setFont(font);
  dialog.setString("Ta funcionando o trem");
  dialog.setCharacterSize(90);
  dialog.setFillColor(sf::Color::White);
}

void TextBox::RenderDialog(Window &EngineWindow) {
  setText();

  while (EngineWindow.mainWindow.isOpen()) {
    EngineWindow.mainWindow.clear();
    EngineWindow.mainWindow.draw(dialog);
    EngineWindow.mainWindow.display();
  }
}