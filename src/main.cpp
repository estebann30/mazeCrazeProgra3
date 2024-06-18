// main.cpp
#include <SFML/Graphics.hpp>
#include "MenuUI.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Menu de Inicio", sf::Style::Titlebar | sf::Style::Close);
    //for static window

    Menu menu(window);
    try {
        Menu menu(window);
        menu.run();
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}