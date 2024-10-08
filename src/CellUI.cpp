#include "CellUI.hpp"

Cell::Cell() {

    if (!loadTextures()) {
        throw std::runtime_error("Failed to load textures"); //exception
    }

    // Set up the base sprite (cell completely open) with the specified scale
    cellSprite.setTexture(cellTexture);
    cellSprite.setScale(static_cast<float>(CELL_SIZE) / cellTexture.getSize().x, static_cast<float>(CELL_SIZE) / cellTexture.getSize().y); // Set the scale to (0.1f, 0.1f)

    upperWallSprite.setTexture(upperWallTexture);
    leftWallSprite.setTexture(leftWallTexture);
    rightWallSprite.setTexture(rightWallTexture);
    belowWallSprite.setTexture(belowWallTexture);
  
}

bool Cell::loadTextures() {

    if (!cellTexture.loadFromFile("./assets/suelo.jpg") || 
        !upperWallTexture.loadFromFile("./assets/cinta.jpg") ||  
        !leftWallTexture.loadFromFile("./assets/cintaVertical.jpg") ||        
        !rightWallTexture.loadFromFile("./assets/cintaVertical.jpg") ||
        !belowWallTexture.loadFromFile("./assets/cinta.jpg")) {
        return false; //exception
    }
    return true;
}

void Cell::adjustWallSprites(const sf::Vector2u &textureSize) {
    
    sf::Vector2u up_and_below_wallTextureSize = upperWallTexture.getSize(); //for the wall on the top and below
    sf::Vector2u right_and_left_wallTextureSize = rightWallTexture.getSize();

    // Calculate scale based on the texture size of the cell sprite

    //for top and below
    float up_and_below_scaleX = static_cast<float>(CELL_SIZE) / up_and_below_wallTextureSize.x;

    //for right and left
    float right_and_left_scaleY = static_cast<float>(CELL_SIZE) / right_and_left_wallTextureSize.y;

    // Adjust the scales to fit within the scaled cell sprite
    upperWallSprite.setScale(up_and_below_scaleX, 0.1f);
    belowWallSprite.setScale(up_and_below_scaleX, 0.1f);
    leftWallSprite.setScale(0.05f, right_and_left_scaleY);
    rightWallSprite.setScale(0.05f, right_and_left_scaleY);
    
    // Position walls at the edges of the scaled cell sprite
    sf::FloatRect cellBounds = cellSprite.getGlobalBounds();
    upperWallSprite.setPosition(cellBounds.left, cellBounds.top);
    leftWallSprite.setPosition(cellBounds.left, cellBounds.top);
    rightWallSprite.setPosition(cellBounds.left + cellBounds.width - rightWallSprite.getGlobalBounds().width, cellBounds.top);
    belowWallSprite.setPosition(cellBounds.left, cellBounds.top + cellBounds.height - belowWallSprite.getGlobalBounds().height);
}


void Cell::draw(sf::RenderWindow& window, Explorer& explorer, int x, int y) { 

    auto& zone = explorer.dungeon().mapped();
    sf::Vector2u textureSize = cellTexture.getSize();
    adjustWallSprites(textureSize);
    window.draw(cellSprite);

    if (zone[y][x]->getNorth() == nullptr) {
        window.draw(upperWallSprite);
    }
    if (zone[y][x]->getEast() == nullptr) {
        window.draw(rightWallSprite);
    }
    if (zone[y][x]->getWest() == nullptr) {
        window.draw(leftWallSprite);
    }
    if (zone[y][x]->getSouth() == nullptr) {
        window.draw(belowWallSprite);
    }
}