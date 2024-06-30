// menu.hpp
#ifndef MENUUI_HPP
#define MENUUI_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.h"
#include "Config.h"
#include "WindowSizeException.h"

class Menu {
public:
    Menu(sf::RenderWindow &window);
    void run( );
    Game game;

private:
    sf::RenderWindow &window;
    sf::Sprite backgroundSprite;
    sf::Sprite startButtonSprite;
    sf::Sprite exitButtonSprite;
    sf::Sprite openedSprite;
    sf::Texture backgroundTexture;
    sf::Texture startButtonTexture;
    sf::Texture exitButtonTexture;
    sf::Texture openedTexture;

    bool loadTextures();
    void handleEvents( );
    void render();
    bool isSpriteClicked(sf::Sprite sprite);
    //bool state;
};

#endif // MENU_HPP
