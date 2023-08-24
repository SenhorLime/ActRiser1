#ifndef ACTRISE1_WINDOW_HPP
#define ACTRISE1_WINDOW_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Window {
public:
  sf::RenderWindow mainWindow;

public:
  Window();

  sf::Event::EventType HandleEvents();

private:
  void Create(const sf::Vector2u &windowSize, const std::string &windowTitle);
};


#endif //ACTRISE1_WINDOW_HPP
