// menu.hpp
#ifndef MENUUI_HPP
#define MENUUI_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {
public:
    Menu(sf::RenderWindow &window);
    void run();

private:
    sf::RenderWindow &window;
    sf::Sprite backgroundSprite;
    sf::Sprite startButtonSprite;
    sf::Sprite exitButtonSprite;
    sf::Texture backgroundTexture;
    sf::Texture startButtonTexture;
    sf::Texture exitButtonTexture;
    

    bool loadTextures();
    void handleEvents();
    void render();
    bool isSpriteClicked(sf::Sprite sprite);
};

#endif // MENU_HPP
