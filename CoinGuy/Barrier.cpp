#include "Barrier.h"

Barrier::Barrier(sf::Texture& texture, float x, float y, float scale)
    : m_sprite(texture)
{
    m_sprite.setScale({ scale, scale });
    m_sprite.setPosition({ x, y });
    auto sz = texture.getSize();
    m_bounds = sf::FloatRect({ x, y }, { sz.x * scale, sz.y * scale });
}

void Barrier::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

sf::FloatRect Barrier::getBounds() const
{
    return m_bounds;
}