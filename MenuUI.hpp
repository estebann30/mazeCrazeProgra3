// menu.hpp
#ifndef MENUUI_HPP
#define MENUUI_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {
public:
    Menu(sf::RenderWindow &window);
    void run(bool open);

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
    void handleEvents(bool open);
    void render();
    bool isSpriteClicked(sf::Sprite sprite);
    //bool state;
};

#endif // MENU_HPP
