#ifndef ACTRISE1_SPLASHSCREEN_HPP
#define ACTRISE1_SPLASHSCREEN_HPP

#include "../../Headers/Window.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class SplashScreen {
public:
  void Show(Window &EngineWindow);

private:
  sf::Sprite LoadSprites();
};


#endif //ACTRISE1_SPLASHSCREEN_HPP
