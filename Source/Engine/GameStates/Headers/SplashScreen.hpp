#ifndef ACTRISE1_SPLASHSCREEN_HPP
#define ACTRISE1_SPLASHSCREEN_HPP

#include "InitialStatesRender.hpp"

class SplashScreen : public InitialStatesRender {
public:
  void Show(Window &EngineWindow);

  void HandleEvents(Window &EngineWindow, sf::Event &event);
};


#endif //ACTRISE1_SPLASHSCREEN_HPP
