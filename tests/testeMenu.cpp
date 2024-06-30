#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Config.h"
#include "WindowSizeException.h"
#include "MenuUI.hpp"

int main() {
    // Crear una ventana SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Menu Example");

    try {
        // Crear una instancia del menú
        Menu menu(window);

        // Ejecutar el menú
        menu.run();
    } catch (const std::runtime_error &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}