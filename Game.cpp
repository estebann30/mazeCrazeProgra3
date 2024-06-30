#include "Game.h"

Game::Game(Explorer& explorer)
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MazeCraze"),
      turnPlayer(true){
    
    totalWidth = MAZE_WIDTH * CELL_SIZE;
    totalHeight = MAZE_HEIGHT * CELL_SIZE;

    if(totalWidth > WINDOW_WIDTH || totalHeight > WINDOW_HEIGHT) {
        throw WindowSizeException("El tamaño total de las casillas excede el tamaño de la ventana");
    }
    if(CELL_SIZE<50){
        throw WindowSizeException("El tamaño de la casilla es muy pequeña");
    }
    if(CELL_SIZE>120){
        throw WindowSizeException("El tamaño de la casilla es muy grande");
    }
    if(WINDOW_WIDTH>1775||WINDOW_HEIGHT>600){
        throw WindowSizeException("El tamaño de la ventana es muy grande");
    }
    if(WINDOW_WIDTH<800||WINDOW_HEIGHT<500){
        throw WindowSizeException("El tamaño de la ventana es muy pequeña");
    }

    if (!texture.loadFromFile("assets/todoAbierto.jpeg")) {
        std::cerr << "Error al cargar la imagen del fondo" << std::endl;
        throw std::runtime_error("Error al cargar la imagen del fondo");
    }

    sprite.setTexture(texture);
    sprite.setScale(static_cast<float>(CELL_SIZE) / texture.getSize().x, static_cast<float>(CELL_SIZE) / texture.getSize().y);
    spriteBounds = sprite.getGlobalBounds();

    totalSpritesX = MAZE_WIDTH;
    totalSpritesY = MAZE_HEIGHT;

    offsetX = (WINDOW_WIDTH - (totalSpritesX * CELL_SIZE)) / 2.0f;
    offsetY = (WINDOW_HEIGHT - (totalSpritesY * CELL_SIZE)) / 2.0f;

    if (!playerTexture.loadFromFile("assets/mago.png")) {
        std::cerr << "Error al cargar la imagen del jugador" << std::endl;
        throw std::runtime_error("Error al cargar la imagen del jugador");
    }

    player1.setTexture(playerTexture);
    player2.setTexture(playerTexture);

    float playerScale = 0.6f; 
    player1.setScale(playerScale * CELL_SIZE / playerTexture.getSize().x, playerScale * CELL_SIZE / playerTexture.getSize().y);
    player2.setScale(playerScale * CELL_SIZE / playerTexture.getSize().x, playerScale * CELL_SIZE / playerTexture.getSize().y);

    if (!fondoTexture.loadFromFile("assets/fondo.jpeg")) {
        std::cerr << "Error al cargar la imagen del fondo" << std::endl;
        throw std::runtime_error("Error al cargar la imagen del fondo");
    }
    spriteFondo.setTexture(fondoTexture);
    spriteFondo.setScale(static_cast<float>(WINDOW_WIDTH) / fondoTexture.getSize().x, static_cast<float>(WINDOW_HEIGHT) / fondoTexture.getSize().y);

    if (!powerTexture1.loadFromFile("assets/cambioDeTurnos.png")) {
        std::cerr << "Error al cargar la imagen del poder 1" << std::endl;
        throw std::runtime_error("Error al cargar la imagen del poder 1");
    }
    if (!powerTexture2.loadFromFile("assets/fichaCon2.png")) {
        std::cerr << "Error al cargar la imagen del poder 2" << std::endl;
        throw std::runtime_error("Error al cargar la imagen del poder 2");
    }
    if (!powerTexture3.loadFromFile("assets/Portal.png")) {
        std::cerr << "Error al cargar la imagen del poder 3" << std::endl;
        throw std::runtime_error("Error al cargar la imagen del poder 3");
    }
    if (!powerTexture4.loadFromFile("assets/Saltar.png")) {
        std::cerr << "Error al cargar la imagen del poder 4" << std::endl;
        throw std::runtime_error("Error al cargar la imagen del poder 4");
    }
    if (!treasureTexture.loadFromFile("assets/tesoro.png")) {
        std::cerr << "Error al cargar la imagen del tesoro" << std::endl;
        throw std::runtime_error("Error al cargar la imagen del tesoro");
    }
    if (!font.loadFromFile("assets/PIXEARG_.TTF")) {
        std::cerr << "Error al cargar la fuente" << std::endl;
        throw std::runtime_error("Error al cargar la fuente");
    }

    player1JumpText.setFont(font);
    player1JumpText.setCharacterSize(20);
    player1JumpText.setFillColor(sf::Color::White);
    player1JumpText.setPosition(10, 10);

    player2JumpText.setFont(font);
    player2JumpText.setCharacterSize(20);
    player2JumpText.setFillColor(sf::Color::White);
    player2JumpText.setPosition(10, 40);

    turnText.setFont(font);
    turnText.setCharacterSize(20);
    turnText.setFillColor(sf::Color::White);
    turnText.setPosition(WINDOW_WIDTH - 180, 10);
}

void Game::run(Explorer& explorer) {

    while (window.isOpen()) {
        
        processEvents();
        update(explorer);
        render(explorer);
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::Closed:
                window.close();
                break;
        }
    }
}

void Game::update(Explorer& explorer) {
    // checkPowerCollision(player1);
    // checkPowerCollision(player2);
    player1JumpText.setString("Player 1 Jumps: " + std::to_string(explorer.getJumps(1)));
    player2JumpText.setString("Player 2 Jumps: " + std::to_string(explorer.getJumps(2)));
    turnText.setString(("Player "+std::to_string(explorer.getPlayer())+ " Turn"));
}

void Game::render(Explorer& explorer) {
    auto& zone = explorer.dungeon().mapped();

    window.clear();

    window.draw(spriteFondo);

    for (int x = 0; x < totalSpritesX; x++) {
        for (int y = 0; y < totalSpritesY; y++) {

            if(startedOnce == false){
                cell[x][y].cellSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE, offsetY + y * CELL_SIZE));
            }
            

            cell[x][y].draw(window, explorer, x, y);

            if (zone[x][y]->getContain()=='@') {
                sf::Sprite powerSprite(powerTexture1);
                powerSprite.setScale(0.6f * CELL_SIZE / powerTexture1.getSize().x, 0.6f * CELL_SIZE / powerTexture1.getSize().y);
                powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                     offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                window.draw(powerSprite);
            }
             if (zone[x][y]->getContain()=='%') {
                 sf::Sprite powerSprite(powerTexture2);
                 powerSprite.setScale(0.6f * CELL_SIZE / powerTexture2.getSize().x, 0.6f * CELL_SIZE / powerTexture2.getSize().y);
                 powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                      offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                 window.draw(powerSprite);
             }
            if (zone[x][y]->getContain()=='<') {
                sf::Sprite powerSprite(powerTexture3);
                powerSprite.setScale(0.6f * CELL_SIZE / powerTexture3.getSize().x, 0.6f * CELL_SIZE / powerTexture3.getSize().y);
                powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                     offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                window.draw(powerSprite);
            }
            if (zone[x][y]->getContain()=='>') {
                sf::Sprite powerSprite(powerTexture3);
                powerSprite.setScale(0.6f * CELL_SIZE / powerTexture3.getSize().x, 0.6f * CELL_SIZE / powerTexture3.getSize().y);
                powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                     offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                window.draw(powerSprite);
            }
            if (zone[x][y]->getContain()=='v') {
                sf::Sprite powerSprite(powerTexture3);
                powerSprite.setScale(0.6f * CELL_SIZE / powerTexture3.getSize().x, 0.6f * CELL_SIZE / powerTexture3.getSize().y);
                powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                     offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                window.draw(powerSprite);
            }
            if (zone[x][y]->getContain()=='^') {
                sf::Sprite powerSprite(powerTexture3);
                powerSprite.setScale(0.6f * CELL_SIZE / powerTexture3.getSize().x, 0.6f * CELL_SIZE / powerTexture3.getSize().y);
                powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                     offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                window.draw(powerSprite);
            }
            if (zone[x][y]->getContain()=='&') {
                sf::Sprite powerSprite(powerTexture4);
                powerSprite.setScale(0.6f* CELL_SIZE / powerTexture4.getSize().x, 0.6f * CELL_SIZE / powerTexture4.getSize().y);
                powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                     offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                window.draw(powerSprite);
            }
            if (zone[x][y]->getContain()=='$') {
                sf::Sprite powerSprite(treasureTexture);
                powerSprite.setScale(0.3f * CELL_SIZE / treasureTexture.getSize().x, 0.3f * CELL_SIZE / treasureTexture.getSize().y);
                powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                     offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                window.draw(powerSprite);
            }
        }
    }

    startedOnce = true;

    player1.setPosition(sf::Vector2f(offsetX + explorer.getX(1) * CELL_SIZE + (CELL_SIZE - player1.getGlobalBounds().width) / 2.0f,
                            offsetY + explorer.getY(1) * CELL_SIZE + (CELL_SIZE - player1.getGlobalBounds().height) / 2.0f));
        window.draw(player1);
    player2.setPosition(sf::Vector2f(offsetX + explorer.getX(2) * CELL_SIZE + (CELL_SIZE - player2.getGlobalBounds().width) / 2.0f,
                        offsetY + explorer.getY(2) * CELL_SIZE + (CELL_SIZE - player2.getGlobalBounds().height) / 2.0f));
        window.draw(player2);

    // for (int x = 0; x < totalSpritesX; ++x) {
    //     for (int y = 0; y < totalSpritesY; ++y) {
            
    //     }
    // }
    window.draw(player1JumpText);
    window.draw(player2JumpText);
    window.draw(turnText);
    window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (!isPressed) return;

    std::string direction;
    std::string currentPlayer = (turnPlayer) ? "player1" : "player2";

    if (currentPlayer == "player1") {
        if (key == sf::Keyboard::W) direction = "up";
        else if (key == sf::Keyboard::S) direction = "down";
        else if (key == sf::Keyboard::A) direction = "left";
        else if (key == sf::Keyboard::D) direction = "right";
    } else if (currentPlayer == "player2") {
        if (key == sf::Keyboard::Up) direction = "up";
        else if (key == sf::Keyboard::Down) direction = "down";
        else if (key == sf::Keyboard::Left) direction = "left";
        else if (key == sf::Keyboard::Right) direction = "right";
    }

    if (!direction.empty()) {
        sendEventToBackend("move", currentPlayer, direction);
        turnPlayer = !turnPlayer; 
    }
}


// void Game::checkPowerCollision(sf::Sprite& player) {
//     sf::Vector2f playerPosition = player.getPosition();
//     int x = (playerPosition.x - offsetX) / CELL_SIZE;
//     int y = (playerPosition.y - offsetY) / CELL_SIZE;
//     if (x >= 0 && x < totalSpritesX && y >= 0 && y < totalSpritesY) {
//         Node& node = grid.getNode(x, y);
//         if (node.hasPower1) {
//             node.hasPower1 = false;
//         }
//         if (node.hasPower2) {
//             node.hasPower2 = false;
//         }
//         if (node.hasPower3) {
//             node.hasPower3 = false;
//         }
//         if (node.hasPower4) {
//             node.hasPower4 = false;
//         }
//     }
// }

// void Game::receiveGrid(Explorer& explorer) {
//     auto& zone= explorer.dungeon().mapped();
//     for (int x = 0; x < MAZE_WIDTH; ++x) {
//         for (int y = 0; y < MAZE_HEIGHT; ++y) {
//             grid.setNode(x, y, zone[x][y]);
//         }
//     }
// }

void Game::sendEventToBackend(const std::string& event, const std::string& player, const std::string& direction) {
    std::cout << "Evento enviado al backend: " << event << " Jugador: " << player << " Dirección: " << direction << std::endl;
}

