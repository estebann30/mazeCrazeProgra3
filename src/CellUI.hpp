#ifndef CELLUI_HPP
#define CELLUI_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Cell {
public:
    Cell(sf::RenderWindow &window);
    void run();
    void configureWalls(bool upper, bool right, bool left, bool below);

private:
    void handleWalls();
    void render();
    void adjustWallSprites(const sf::Vector2u &windowSize); //adjust Walls to tey respective position
    bool loadTextures();

    sf::RenderWindow &window;

    sf::Sprite cellSprite; //background
    sf::Sprite upperWallSprite;
    sf::Sprite leftWallSprite;
    sf::Sprite rightWallSprite;
    sf::Sprite belowWallSprite;

    sf::Texture cellTexture;  //background
    sf::Texture upperWallTexture;
    sf::Texture leftWallTexture;
    sf::Texture rightWallTexture;
    sf::Texture belowWallTexture;
 
    //lo que se deberia leer del backend
    bool upperWall;
    bool rightWall;
    bool leftWall;
    bool belowWall;
};

#endif
