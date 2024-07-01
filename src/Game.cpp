#include "Game.h"

Game::Game(Explorer& explorer,  Controller& controller)
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

    if (!player1Texture.loadFromFile("assets/player1.png")) {
        std::cerr << "Error al cargar la imagen del jugador" << std::endl;
        throw std::runtime_error("Error al cargar la imagen del jugador 1");
    }
    if (!player2Texture.loadFromFile("assets/player2.png")) {
        std::cerr << "Error al cargar la imagen del jugador" << std::endl;
        throw std::runtime_error("Error al cargar la imagen del jugador 2");
    }


    player1.setTexture(player1Texture);
    player2.setTexture(player2Texture);

    float playerScale = 0.6f; 
    player1.setScale(playerScale * CELL_SIZE / player1Texture.getSize().x, playerScale * CELL_SIZE / player1Texture.getSize().y);
    player2.setScale(playerScale * CELL_SIZE / player2Texture.getSize().x, playerScale * CELL_SIZE / player2Texture.getSize().y);

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
    if (!player_1_wins_texture.loadFromFile("assets/player1_wins.jpeg")) {
        throw std::runtime_error("Error al cargar la imagen de ganador");
    }
    if (!player_2_wins_texture.loadFromFile("assets/player2_wins.jpeg")) {
        throw std::runtime_error("Error al cargar la imagen de ganador");
    }
    if (!ambientMusicBuffer.loadFromFile("assets/dungeon_ambient_1.ogg")) {
        throw std::runtime_error("Error al cargar el sonido ambiente");
    
    }
    if (!victorySongBuffer.loadFromFile("assets/victorySong.wav")) {
        throw std::runtime_error("Error al cargar el sonido de la victoria");
    
    }
    
    victorySongSound.setBuffer(victorySongBuffer);
    ambientMusicSound.setBuffer(ambientMusicBuffer);

    player_1_wins_sprite.setTexture(player_1_wins_texture);
    player_1_wins_sprite.setScale(static_cast<float>(WINDOW_WIDTH) / player_1_wins_texture.getSize().x, static_cast<float>(WINDOW_HEIGHT) / player_1_wins_texture.getSize().y);

    player_2_wins_sprite.setTexture(player_2_wins_texture);
    player_2_wins_sprite.setScale(static_cast<float>(WINDOW_WIDTH) / player_2_wins_texture.getSize().x, static_cast<float>(WINDOW_HEIGHT) / player_2_wins_texture.getSize().y);


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

void Game::run(Explorer& explorer,  Controller& controller) {

    ambientMusicSound.setLoop(true);
    ambientMusicSound.play();

    while (window.isOpen()) {

        processEvents(explorer, controller);
        
        if(explorer.getWinner() == 0){
            update(explorer);
            render(explorer);
        }

        if (explorer.getWinner() == 2){

            ambientMusicSound.stop();
            
            window.clear();
            window.draw(player_2_wins_sprite);
            window.display();


            victorySongSound.play();
            sf::sleep(sf::milliseconds(6000)); //let the music play
            window.close();

        }

        if (explorer.getWinner() == 1){

            ambientMusicSound.stop();
            
            window.clear();
            window.draw(player_1_wins_sprite);
            window.display();

            victorySongSound.play();
            sf::sleep(sf::milliseconds(6000)); //let the music play
            window.close();

        };
    }   
}

void Game::processEvents(Explorer& explorer,  Controller& controller) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true, explorer, controller);
                break;
            case sf::Event::Closed:
                window.close();
                break;
        }
    }
}

void Game::update(Explorer& explorer) {

    player1JumpText.setString("Player 1 Jumps: " + std::to_string(explorer.getJumps(1)));
    player2JumpText.setString("Player 2 Jumps: " + std::to_string(explorer.getJumps(2)));
    turnText.setString(("Player "+std::to_string(explorer.getPlayer())+ " Turn"));
}

void Game::render(Explorer& explorer) {
    auto& zone = explorer.dungeon().mapped();

    window.clear();

    window.draw(spriteFondo);

    for (int x = 0; x < zone.size(); x++) {
        for (int y = 0; y < zone[0].size(); y++) {

            
            cell[x][y].cellSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE, offsetY + y * CELL_SIZE));
            
            
            if(zone[y][x] != nullptr){
                
                cell[x][y].cellSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE, offsetY + y * CELL_SIZE));
                cell[x][y].draw(window, explorer, x, y);
            }


            if (zone[y][x]->getContain()=='@') {
                sf::Sprite powerSprite(powerTexture1);
                powerSprite.setScale(0.6f * CELL_SIZE / powerTexture1.getSize().x, 0.6f * CELL_SIZE / powerTexture1.getSize().y);
                powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                     offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                window.draw(powerSprite);
            }
             if (zone[y][x]->getContain()=='%') {
                 sf::Sprite powerSprite(powerTexture2);
                 powerSprite.setScale(0.6f * CELL_SIZE / powerTexture2.getSize().x, 0.6f * CELL_SIZE / powerTexture2.getSize().y);
                 powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                      offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                 window.draw(powerSprite);
             }
            if (zone[y][x]->getContain()=='<') {
                sf::Sprite powerSprite(powerTexture3);
                powerSprite.setScale(0.6f * CELL_SIZE / powerTexture3.getSize().x, 0.6f * CELL_SIZE / powerTexture3.getSize().y);
                powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                     offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                window.draw(powerSprite);
            }
            if (zone[y][x]->getContain()=='>') {
                sf::Sprite powerSprite(powerTexture3);
                powerSprite.setScale(0.6f * CELL_SIZE / powerTexture3.getSize().x, 0.6f * CELL_SIZE / powerTexture3.getSize().y);
                powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                     offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                window.draw(powerSprite);
            }
            if (zone[y][x]->getContain()=='v') {
                sf::Sprite powerSprite(powerTexture3);
                powerSprite.setScale(0.6f * CELL_SIZE / powerTexture3.getSize().x, 0.6f * CELL_SIZE / powerTexture3.getSize().y);
                powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                     offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                window.draw(powerSprite);
            }
            if (zone[y][x]->getContain()=='^') {
                sf::Sprite powerSprite(powerTexture3);
                powerSprite.setScale(0.6f * CELL_SIZE / powerTexture3.getSize().x, 0.6f * CELL_SIZE / powerTexture3.getSize().y);
                powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                     offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                window.draw(powerSprite);
            }
            if (zone[y][x]->getContain()=='&') {
                sf::Sprite powerSprite(powerTexture4);
                powerSprite.setScale(0.6f* CELL_SIZE / powerTexture4.getSize().x, 0.6f * CELL_SIZE / powerTexture4.getSize().y);
                powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                     offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                window.draw(powerSprite);
            }
            if (zone[y][x]->getContain()=='$') {
                sf::Sprite powerSprite(treasureTexture);
                powerSprite.setScale(0.3f * CELL_SIZE / treasureTexture.getSize().x, 0.3f * CELL_SIZE / treasureTexture.getSize().y);
                powerSprite.setPosition(sf::Vector2f(offsetX + x * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().width) / 2.0f,
                                                     offsetY + y * CELL_SIZE + (CELL_SIZE - powerSprite.getGlobalBounds().height) / 2.0f));
                window.draw(powerSprite);
            }
        }
    }

    startedOnce = true;

    player1.setPosition(sf::Vector2f(offsetX + explorer.getY(1) * CELL_SIZE + (CELL_SIZE - player1.getGlobalBounds().width) / 2.0f,
                            offsetY + explorer.getX(1) * CELL_SIZE + (CELL_SIZE - player1.getGlobalBounds().height) / 2.0f));
        window.draw(player1);
    player2.setPosition(sf::Vector2f(offsetX + explorer.getY(2) * CELL_SIZE + (CELL_SIZE - player2.getGlobalBounds().width) / 2.0f,
                        offsetY + explorer.getX(2) * CELL_SIZE + (CELL_SIZE - player2.getGlobalBounds().height) / 2.0f));
        window.draw(player2);

    
    window.draw(player1JumpText);
    window.draw(player2JumpText);
    window.draw(turnText);
    window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed, Explorer& explorer, Controller& controller) {
    if (!isPressed) return;

    char direction;

    if (explorer.getPlayer() == 1) {
        if (key == sf::Keyboard::W) direction = 'w';
        else if (key == sf::Keyboard::S) direction = 's';
        else if (key == sf::Keyboard::A) direction = 'a';
        else if (key == sf::Keyboard::D) direction = 'd';
    } else if (explorer.getPlayer() == 2) {
        if (key == sf::Keyboard::Up) direction = 'I';
        else if (key == sf::Keyboard::Down) direction = 'K';
        else if (key == sf::Keyboard::Left) direction = 'J';
        else if (key == sf::Keyboard::Right) direction = 'L';
    }

    if (direction != '\0') { //no es nulo
        sendEventToBackend(direction, explorer, controller);
    }
}

void Game::sendEventToBackend(char direction, Explorer& explorer, Controller& controller) {

    controller.pad(explorer, direction);


    

}

