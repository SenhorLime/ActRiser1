#include "Headers/Window.hpp"

Window::Window() { Create(sf::Vector2u(1024, 576), "Act Riser"); }

void Window::Create(const sf::Vector2u &windowSize, const std::string &windowTitle) {
  mainWindow.create({windowSize.x, windowSize.y}, windowTitle);
}

sf::Event::EventType Window::HandleEvents() {
  sf::Event event;

  while (mainWindow.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        mainWindow.close();
        break;
    }
  }

  return event.type;
}