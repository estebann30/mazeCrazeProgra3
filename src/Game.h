#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Config.h"
#include "CellUI.hpp"
#include "Controller.h"
#include "WindowSizeException.h"
#include "Chunk.h"
#include "Explorer.h"

class Game {
public:
    Game(Explorer& explorer, Controller& controller);
    void run(Explorer& explorer, Controller& controller);
    void sendEventToBackend(char direction, Explorer& explorer, Controller& controller);

private:
    void processEvents(Explorer& explorer,  Controller& controller);
    void update(Explorer& explorer);
    void render(Explorer& explorer);
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed, Explorer& explorer, Controller& controller);

private:
    sf::RenderWindow window;
    sf::Texture texture;
    sf::Sprite sprite;

    Cell cell[MAZE_WIDTH][MAZE_HEIGHT]; //create all cell objects

    sf::SoundBuffer ambientMusicBuffer;
    sf::Sound ambientMusicSound;
    sf::SoundBuffer victorySongBuffer;
    sf::Sound victorySongSound;

    sf::Texture player_1_wins_texture;
    sf::Sprite player_1_wins_sprite;
    sf::Texture player_2_wins_texture;
    sf::Sprite player_2_wins_sprite;
    sf::Texture player1Texture;
    sf::Texture player2Texture;
    sf::Sprite player1;
    sf::Sprite player2;
    sf::Texture powerTexture1;
    sf::Texture powerTexture2;
    sf::Texture powerTexture3;
    sf::Texture powerTexture4;
    sf::Texture treasureTexture;
    sf::Sprite treasure;
    sf::FloatRect spriteBounds;

    int totalSpritesX;
    int totalSpritesY;
    float offsetX;
    float offsetY;

    sf::Texture fondoTexture;
    sf::Sprite spriteFondo;
    sf::Font font;
    sf::Text player1JumpText;
    sf::Text player2JumpText;
    
    int player1JumpCount;
    int player2JumpCount;
    sf::Text turnText;
    int totalWidth;
    int totalHeight;
    bool turnPlayer;
};

#endif // GAME_H
