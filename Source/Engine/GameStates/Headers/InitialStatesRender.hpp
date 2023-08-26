#ifndef ACTRISE1_INITIALSTATESRENDER_HPP
#define ACTRISE1_INITIALSTATESRENDER_HPP

#include "../../Headers/Window.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class InitialStatesRender {
public:
  void Show(Window &EngineWindow);

  void HandleEvents(Window &EngineWindow, sf::Event &event);

  void LoadSprites(std::string filePath) {
    texture.loadFromFile(filePath);
    sprite.setTexture(texture);
  };

protected:
  sf::Sprite sprite;
  sf::Texture texture;
};

#endif //ACTRISE1_INITIALSTATESRENDER_HPP
