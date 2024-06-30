#ifndef CELLUI_HPP
#define CELLUI_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Config.h"

class Cell {
public:
    Cell();
    void draw(sf::RenderWindow& window);
    void drawNorth(sf::RenderWindow& window);
    void drawEast(sf::RenderWindow& window);
    void drawSouth(sf::RenderWindow& window);
    void drawWest(sf::RenderWindow& window);

    sf::Sprite cellSprite; //floor

private:
    void adjustWallSprites(const sf::Vector2u &textureSize);
    bool loadTextures();

    sf::Sprite upperWallSprite;
    sf::Sprite leftWallSprite;
    sf::Sprite rightWallSprite;
    sf::Sprite belowWallSprite;

    sf::Texture cellTexture;      //floor
    sf::Texture upperWallTexture;
    sf::Texture leftWallTexture;
    sf::Texture rightWallTexture;
    sf::Texture belowWallTexture;
 
};

#endif
