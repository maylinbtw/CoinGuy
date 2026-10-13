#pragma once
#include <SFML/Graphics.hpp>

class Barrier
{
public:
    Barrier(sf::Texture& texture, float x, float y, float scale = 1.f);

    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

private:
    sf::Sprite m_sprite;
    sf::FloatRect m_bounds;
};