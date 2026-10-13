#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Platform
{
public:
    Platform(sf::Texture& texture, float x, float y, float w, float h);

    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

private:
    std::vector<sf::Sprite> m_tiles;
    sf::FloatRect m_bounds;
};