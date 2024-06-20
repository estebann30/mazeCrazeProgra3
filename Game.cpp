#include "Game.h"

// Constructor que inicializa el juego
Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MazeCraze"),
      grid(MAZE_WIDTH, MAZE_HEIGHT) {

    // Cargar la textura del fondo
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

    // Cargar la textura del jugador
    if (!playerTexture.loadFromFile("assets/mago.png")) {
        std::cerr << "Error al cargar la imagen del jugador" << std::endl;
        throw std::runtime_error("Error al cargar la imagen del jugador");
    }

    // Inicializar los sprites de los jugadores
    player1.setTexture(playerTexture);
    player2.setTexture(playerTexture);

    float playerScale = 0.6f; // Escala del jugador en relación a la celda
    player1.setScale(playerScale * CELL_SIZE / playerTexture.getSize().x, playerScale * CELL_SIZE / playerTexture.getSize().y);
    player2.setScale(playerScale * CELL_SIZE / playerTexture.getSize().x, playerScale * CELL_SIZE / playerTexture.getSize().y);

    // Cargar la textura del fondo de la ventana
    if (!fondoTexture.loadFromFile("assets/fondo.jpeg")) {
        std::cerr << "Error al cargar la imagen del fondo" << std::endl;
        throw std::runtime_error("Error al cargar la imagen del fondo");
    }
    spriteFondo.setTexture(fondoTexture);
    spriteFondo.setScale(static_cast<float>(WINDOW_WIDTH) / fondoTexture.getSize().x, static_cast<float>(WINDOW_HEIGHT) / fondoTexture.getSize().y);

    // Cargar las texturas de los poderes
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
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S ||
                event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) {
                // Mueve al jugador 1
                sf::Vector2f offset(0, 0);
                std::string direction;
                if (event.key.code == sf::Keyboard::W) {
                    offset.y = -CELL_SIZE;
                    direction = "up";
                }
                if (event.key.code == sf::Keyboard::S) {
                    offset.y = CELL_SIZE;
                    direction = "down";
                }
                if (event.key.code == sf::Keyboard::A) {
                    offset.x = -CELL_SIZE;
                    direction = "left";
                }
                if (event.key.code == sf::Keyboard::D) {
                    offset.x = CELL_SIZE;
                    direction = "right";
                }
                player1.setPosition(player1.getPosition() + offset);
                sendEventToBackend("PlayerMoved", "Player1", direction);
            }
            if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down ||
                event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
                // Mueve al jugador 2
                sf::Vector2f offset(0, 0);
                std::string direction;
                if (event.key.code == sf::Keyboard::Up) {
                    offset.y = -CELL_SIZE;
                    direction = "up";
                }
                if (event.key.code == sf::Keyboard::Down) {
                    offset.y = CELL_SIZE;
                    direction = "down";
                }
                if (event.key.code == sf::Keyboard::Left) {
                    offset.x = -CELL_SIZE;
                    direction = "left";
                }
                if (event.key.code == sf::Keyboard::Right) {
                    offset.x = CELL_SIZE;
                    direction = "right";
                }
                player2.setPosition(player2.getPosition() + offset);
                sendEventToBackend("PlayerMoved", "Player2", direction);
            }
        }
    }
}

void Game::update() {
    checkPowerCollision(player1);
    checkPowerCollision(player2);
}

void Game::render() {
    window.clear();

    window.draw(spriteFondo);

    for (int x = 0; x < totalSpritesX; x++) {
        for (int y = 0; y < totalSpritesY; y++) {
            sprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE, offsetY + y * CELL_SIZE));
            window.draw(sprite);

            Node& node = grid.getNode(x, y);
            if (node.hasPower1) {
                sf::Sprite powerSprite(powerTexture1);
                powerSprite.setScale(0.6f * CELL_SIZE / powerTexture1.getSize().x, 0.6f * CELL_SIZE / powerTexture1.getSize().y);
                powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                     offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                window.draw(powerSprite);
            }
            if (node.hasPower2) {
                sf::Sprite powerSprite(powerTexture2);
                powerSprite.setScale(0.6f * CELL_SIZE / powerTexture2.getSize().x, 0.6f * CELL_SIZE / powerTexture2.getSize().y);
                powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                     offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                window.draw(powerSprite);
            }
            if (node.hasPower3) {
                sf::Sprite powerSprite(powerTexture3);
                powerSprite.setScale(0.6f * CELL_SIZE / powerTexture3.getSize().x, 0.6f * CELL_SIZE / powerTexture3.getSize().y);
                powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                     offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                window.draw(powerSprite);
            }
            if (node.hasPower4) {
                sf::Sprite powerSprite(powerTexture4);
                powerSprite.setScale(0.6f * CELL_SIZE / powerTexture4.getSize().x, 0.6f * CELL_SIZE / powerTexture4.getSize().y);
                powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                     offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                window.draw(powerSprite);
            }
        }
    }

    // Renderizar jugadores
    for (int x = 0; x < totalSpritesX; ++x) {
        for (int y = 0; y < totalSpritesY; ++y) {
            Node& node = grid.getNode(x, y);
            if (node.hasPlayer1) {
                player1.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - player1.getGlobalBounds().width) / 2.0f,
                                    offsetY + y * CELL_SIZE + (CELL_SIZE - player1.getGlobalBounds().height) / 2.0f));
                window.draw(player1);
            }
            if (node.hasPlayer2) {
                player2.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - player2.getGlobalBounds().width) / 2.0f,
                                    offsetY + y * CELL_SIZE + (CELL_SIZE - player2.getGlobalBounds().height) / 2.0f));
                window.draw(player2);
            }
        }
    }

    window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed, const std::string& player) {
    if (isPressed) {
        std::string direction;
        if (player == "Player1") {
            if (key == sf::Keyboard::W) {
                direction = "up";
            }
            if (key == sf::Keyboard::S) {
                direction = "down";
            }
            if (key == sf::Keyboard::A) {
                direction = "left";
            }
            if (key == sf::Keyboard::D) {
                direction = "right";
            }
        } else {
            if (key == sf::Keyboard::Up) {
                direction = "up";
            }
            if (key == sf::Keyboard::Down) {
                direction = "down";
            }
            if (key == sf::Keyboard::Left) {
                direction = "left";
            }
            if (key == sf::Keyboard::Right) {
                direction = "right";
            }
        }
        if (!direction.empty()) {
            sendEventToBackend("PlayerMoved", player, direction);
        }
    }
}

void Game::checkPowerCollision(sf::Sprite& player) {
    sf::Vector2f playerPosition = player.getPosition();
    int x = (playerPosition.x - offsetX) / CELL_SIZE;
    int y = (playerPosition.y - offsetY) / CELL_SIZE;
    if (x >= 0 && x < totalSpritesX && y >= 0 && y < totalSpritesY) {
        Node& node = grid.getNode(x, y);
        if (node.hasPower1) {
            node.hasPower1 = false;
        }
        if (node.hasPower2) {
            node.hasPower2 = false;
        }
        if (node.hasPower3) {
            node.hasPower3 = false;
        }
        if (node.hasPower4) {
            node.hasPower4 = false;
        }
    }
}

void Game::receiveGrid(const std::vector<std::vector<Node>>& newGrid) {
    for (int x = 0; x < grid.getWidth(); ++x) {
        for (int y = 0; y < grid.getHeight(); ++y) {
            grid.setNode(x, y, newGrid[x][y]);
        }
    }
}

void Game::sendEventToBackend(const std::string& event, const std::string& player, const std::string& direction) {
    std::cout << "Evento enviado al backend: " << event << " Jugador: " << player << " Dirección: " << direction << std::endl;
}

