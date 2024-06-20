#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player(const sf::Texture& texture, const sf::Vector2f& position);

    sf::Vector2f getPosition() const { return sprite.getPosition(); }
    void setPosition(const sf::Vector2f& position) { sprite.setPosition(position); }
    void setScale(float scaleX, float scaleY) { sprite.setScale(scaleX, scaleY); }
    sf::FloatRect getGlobalBounds() const { return sprite.getGlobalBounds(); }
    sf::Sprite& getSprite() { return sprite; }

private:
    sf::Sprite sprite;
};

#endif // PLAYER_H
