// menu.hpp
#ifndef MENUUI_HPP
#define MENUUI_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Config.h"
#include "Game.h"
#include "WindowSizeException.h"

class Menu {
public:
    Menu(sf::RenderWindow &window);
    void run( );
    bool get_status();

    bool status;

private:

    sf::SoundBuffer menuMusicBuffer;
    sf::Sound menuMusicSound;

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
};

#endif // MENU_HPP
