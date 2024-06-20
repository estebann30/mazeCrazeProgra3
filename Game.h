#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Node.h"
#include "Grid.h"
#include "Config.h"

class Game {
public:
    Game();
    void run();

    void receiveGrid(const std::vector<std::vector<Node>>& newGrid);
    void sendEventToBackend(const std::string& event, const std::string& player, const std::string& direction);

private:
    void processEvents();
    void update();
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed, const std::string& player);
    void checkPowerCollision(sf::Sprite& player);

private:
    sf::RenderWindow window;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Texture playerTexture;
    sf::Sprite player1;
    sf::Sprite player2;
    sf::Texture powerTexture1;
    sf::Texture powerTexture2;
    sf::Texture powerTexture3;
    sf::Texture powerTexture4;
    sf::FloatRect spriteBounds;
    int totalSpritesX;
    int totalSpritesY;
    float offsetX;
    float offsetY;
    Grid grid;
    sf::Texture fondoTexture;
    sf::Sprite spriteFondo;
};

#endif // GAME_H
