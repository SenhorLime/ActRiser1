#ifndef ACTRISE1_WINDOW_HPP
#define ACTRISE1_WINDOW_HPP

#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Window {
public:
    Window(); // Construtor da Janela

    void Render(); // Renderiza a janela na tela

    void Draw(sf::Drawable &drawable); // É usado para desenhar algo dentro da janela - AINDA NÃO TESTADO

private:
    void Create(const std::string &windowTitle,
                const sf::Vector2u &windowSize); // Cria a janela com as configurações desejadas

    void HandleEvents(); // É usado para capturar os inputs direcionados diretamente a janela

    sf::RenderWindow window; // Janela
};

#endif //ACTRISE1_WINDOW_HPP
