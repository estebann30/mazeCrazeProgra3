#include "CellUI.hpp"

Cell::Cell(sf::RenderWindow &window) : window(window) {

    if (!loadTextures()) {
        throw std::runtime_error("Failed to load textures"); //exception
    }

    // Set up sprites
    cellSprite.setTexture(cellTexture);
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = cellTexture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    cellSprite.setScale(scaleX, scaleY);

    upperWallSprite.setTexture(upperWallTexture);
    leftWallSprite.setTexture(leftWallTexture);
    rightWallSprite.setTexture(rightWallTexture);
    belowWallSprite.setTexture(belowWallTexture);

    //upperWallSprite.setPosition(400, 505);   //cambiar
    //leftWallSprite.setPosition(300,200);     //cambiar
    //rightWallSprite.setPosition(100,100);    //cambiar
    //belowWallSprite.setPosition(100,100);    //cambiar

    // Adjust wall sprites
    adjustWallSprites(windowSize);

    // Initial wall states
    upperWall = false;
    rightWall = false;
    leftWall = false;
    belowWall = false;
  
}

bool Cell::loadTextures() {
    if (!cellTexture.loadFromFile("../assets/todoAbierto.jpeg") || //background
        !upperWallTexture.loadFromFile("../assets/tapadoArribaa.jpeg") ||  
        !leftWallTexture.loadFromFile("../assets/tapadoCostadoo.jpeg") ||        
        !rightWallTexture.loadFromFile("../assets/tapadoCostadoo.jpeg") ||
        !belowWallTexture.loadFromFile("../assets/tapadoAbajoo.jpeg")) {
        return false; //exception
    }
    return true;
}

void Cell::run() {
    while (window.isOpen()) {
        handleWalls();
        render();
    }
}

void Cell::configureWalls(bool upper, bool right, bool left, bool below) {
    upperWall = upper;
    rightWall = right;
    leftWall = left;
    belowWall = below;
}

void Cell::handleWalls() {

        //to change cells dynamically (portals / powers) maybe??
    
}

void Cell::adjustWallSprites(const sf::Vector2u &windowSize) {
    // Assuming walls are the same width as the cell's border width
    sf::Vector2u wallTextureSize = upperWallTexture.getSize();

    // Scale walls to fit the width or height of the window
    float scaleX = static_cast<float>(windowSize.x) / wallTextureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / wallTextureSize.y;

    upperWallSprite.setScale(scaleX, 1.0f);
    belowWallSprite.setScale(scaleX, 1.0f);
    leftWallSprite.setScale(1.0f, scaleY);
    rightWallSprite.setScale(1.0f, scaleY);

    // Position walls at the edges of the cell
    upperWallSprite.setPosition(0, 0);
    leftWallSprite.setPosition(0, 0);
    rightWallSprite.setPosition(windowSize.x - (wallTextureSize.x * rightWallSprite.getScale().x), 0);
    belowWallSprite.setPosition(0, windowSize.y - (wallTextureSize.y * belowWallSprite.getScale().y));
}

void Cell::render() {
    window.clear();
    window.draw(cellSprite);

    if (upperWall) {
        window.draw(upperWallSprite);
    }
    if (rightWall) {
        window.draw(rightWallSprite);
    }
    if (leftWall) {
        window.draw(leftWallSprite);
    }
    if (belowWall) {
        window.draw(belowWallSprite);
    }

    window.display();
}
