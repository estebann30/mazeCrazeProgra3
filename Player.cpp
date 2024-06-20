#include "Player.h"
#include <iostream>

Player::Player(const sf::Texture& texture, const sf::Vector2f& position) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(0.6f, 0.6f);  // Ajusta la escala del jugador aquí si es necesario
    std::cout << "Player creado en posición: " << position.x << ", " << position.y << " con escala: " << sprite.getScale().x << ", " << sprite.getScale().y << std::endl;
}
