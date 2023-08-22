#include "Headers/Window.hpp"

Window::Window() { Create("Act Riser", sf::Vector2u(1024, 576)); }

void Window::Create(const std::string &windowTitle, const sf::Vector2u &windowSize) {
  window.create({windowSize.x, windowSize.y}, windowTitle);
}

void Window::HandleEvents() {
  sf::Event event;

  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) { window.close(); }
  }
}

void Window::Render() {
  while (window.isOpen()) {
    HandleEvents();

    window.clear();
    window.display();
  }
}

void Window::Draw(sf::Drawable &drawable) { window.draw(drawable); }

