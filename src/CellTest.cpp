#include <SFML/Graphics.hpp>
#include "CellUI.hpp"

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cell UI Test");

    // Create a Cell object
    Cell cell(window);

    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear screen
        window.clear();

        // Draw the cell
        cell.draw(window, true, true, true, true);

        // Update the window
        window.display();
    }

    return 0;
}
