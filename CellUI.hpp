#ifndef CELLUI_HPP
#define CELLUI_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Config.h"
#include "Explorer.h"

class Cell {
public:
    Cell();
    void draw(sf::RenderWindow& window, Explorer& explorer, int x, int y);
    sf::Sprite cellSprite; //background

private:
    void handleWalls();
    void adjustWallSprites(const sf::Vector2u &textureSize); // const sf::Vector2u &textureSize
    bool loadTextures();


    //sf::Sprite cellSprite; //background
    sf::Sprite upperWallSprite;
    sf::Sprite leftWallSprite;
    sf::Sprite rightWallSprite;
    sf::Sprite belowWallSprite;

    sf::Texture cellTexture;  //background
    sf::Texture upperWallTexture;
    sf::Texture leftWallTexture;
    sf::Texture rightWallTexture;
    sf::Texture belowWallTexture;
 
};

#endif
