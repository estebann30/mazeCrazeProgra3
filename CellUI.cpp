#include "CellUI.hpp"

Cell::Cell() {

    if (!loadTextures()) {
        throw std::runtime_error("Failed to load textures"); //exception
    }

    // Set up the base sprite (cell completely open) with the specified scale
    cellSprite.setTexture(cellTexture);
    cellSprite.setScale(0.1f, 0.1f); // Set the scale to (0.1f, 0.1f)

    upperWallSprite.setTexture(upperWallTexture);
    leftWallSprite.setTexture(leftWallTexture);
    rightWallSprite.setTexture(rightWallTexture);
    belowWallSprite.setTexture(belowWallTexture);

    // Adjust wall sprites
    //sf::Vector2u textureSize = cellTexture.getSize();
    //adjustWallSprites(textureSize);
  
}

bool Cell::loadTextures() {

    if (!cellTexture.loadFromFile("./assets/todoAbierto.jpeg") || //background
        !upperWallTexture.loadFromFile("./assets/cinta.jpg") ||  // ../assets/tapadoArribaa.jpeg
        !leftWallTexture.loadFromFile("./assets/tapadoCostadoo.jpeg") ||        
        !rightWallTexture.loadFromFile("./assets/tapadoCostadoo.jpeg") ||
        !belowWallTexture.loadFromFile("./assets/cinta.jpg")) {    // ../assets/tapadoAbajoo.jpeg
        return false; //exception
    }
    return true;
}


void Cell::handleWalls() {

        //to change cells dynamically (portals / powers) maybe??
    
}

void Cell::adjustWallSprites(const sf::Vector2u &textureSize) {
    
    sf::Vector2u up_and_below_wallTextureSize = upperWallTexture.getSize(); //for the wall on the top and below
    sf::Vector2u right_and_left_wallTextureSize = rightWallTexture.getSize();

    // Calculate scale based on the texture size of the cell sprite

    //for top and below
    float up_and_below_scaleX = static_cast<float>(textureSize.x) / up_and_below_wallTextureSize.x;

    //for right and left
    float right_and_left_scaleY = static_cast<float>(textureSize.y) / right_and_left_wallTextureSize.y;

    // Adjust the scales to fit within the scaled cell sprite
    up_and_below_scaleX *= 0.1f;
    right_and_left_scaleY *= 0.1f;


    upperWallSprite.setScale(up_and_below_scaleX, 0.1f);
    belowWallSprite.setScale(up_and_below_scaleX, 0.1f);
    leftWallSprite.setScale(0.1f, right_and_left_scaleY);
    rightWallSprite.setScale(0.1f, right_and_left_scaleY);

    // Position walls at the edges of the scaled cell sprite
    sf::FloatRect cellBounds = cellSprite.getGlobalBounds();
    upperWallSprite.setPosition(cellBounds.left, cellBounds.top);
    leftWallSprite.setPosition(cellBounds.left, cellBounds.top);
    rightWallSprite.setPosition(cellBounds.left + cellBounds.width - rightWallSprite.getGlobalBounds().width, cellBounds.top);
    belowWallSprite.setPosition(cellBounds.left, cellBounds.top + cellBounds.height - belowWallSprite.getGlobalBounds().height);
}


void Cell::draw(sf::RenderWindow& window, bool upper, bool right, bool left, bool below) { 

    sf::Vector2u textureSize = cellTexture.getSize();
    adjustWallSprites(textureSize);
    
    window.draw(cellSprite);

    adjustWallSprites(textureSize);

    if (upper) {
        window.draw(upperWallSprite);
    }
    if (right) {
        window.draw(rightWallSprite);
    }
    if (left) {
        window.draw(leftWallSprite);
    }
    if (below) {
        window.draw(belowWallSprite);
    }

    //window.display();
}
