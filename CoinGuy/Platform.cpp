#include "Platform.h"

Platform::Platform(sf::Texture& texture, float x, float y, float w, float h)
    : m_bounds(sf::Vector2f(x, y), sf::Vector2f(w, h))
{
    float tileW = texture.getSize().x * 0.5f;
    float tileH = texture.getSize().y * 0.5f;

    float cx = x;
    while (cx < x + w)
    {
        sf::Sprite s(texture);
        s.setScale({ 0.5f, 0.5f });
        s.setPosition({ cx, y - 20.f });
        m_tiles.push_back(s);
        cx += tileW;
    }
}

void Platform::draw(sf::RenderWindow& window)
{
    for (auto& s : m_tiles)
        window.draw(s);
}

sf::FloatRect Platform::getBounds() const
{
    return m_bounds;
}