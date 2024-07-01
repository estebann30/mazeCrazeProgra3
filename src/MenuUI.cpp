#include "MenuUI.hpp"

Menu::Menu(sf::RenderWindow &window) : window(window) {
    if (!loadTextures()) {
        throw std::runtime_error("Failed to load textures");
    }

    if (!menuMusicBuffer.loadFromFile("assets/menuMusic.ogg")) {
        throw std::runtime_error("Error al cargar el sonido de la victoria");
    
    }
    menuMusicSound.setBuffer(menuMusicBuffer);

    // Set up sprites
    backgroundSprite.setTexture(backgroundTexture);
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);

    startButtonSprite.setTexture(startButtonTexture);
    exitButtonSprite.setTexture(exitButtonTexture);
    startButtonSprite.setPosition(100, 500);
    exitButtonSprite.setPosition(400, 505);

    openedSprite.setTexture(openedTexture);
    openedSprite.setPosition(500, 100);
}

bool Menu::loadTextures() {
    if (!backgroundTexture.loadFromFile("./assets/menu1.jpeg") ||
        !startButtonTexture.loadFromFile("./assets/startButt.png") ||
        !exitButtonTexture.loadFromFile("./assets/exitButt.png")) {
        return false; //exception
    }
    return true;
}

void Menu::run() {
    
    menuMusicSound.setLoop(true);
    menuMusicSound.play();

    while(window.isOpen()){
        handleEvents();
        render();
    }
    

}

void Menu::handleEvents() {

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (isSpriteClicked(startButtonSprite)) {

                    status = true;
                    menuMusicSound.stop();
                    window.close();

                }
                if (isSpriteClicked(exitButtonSprite)) {
                    
                    status = false;
                    menuMusicSound.stop();
                    window.close();

                }
            }
        }
    }
}

bool Menu::get_status(){
    return status;
}

void Menu::render() {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(startButtonSprite);
    window.draw(exitButtonSprite);
    window.display();
}

bool Menu::isSpriteClicked(sf::Sprite sprite) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
    return sprite.getGlobalBounds().contains(worldPos);
}
