#include "Coin.h"

Coin::Coin(sf::Texture& texture, float x, float y)
    : m_animator(texture, 16, 16)
    , m_position(x, y)
{
    m_animator.addAnimation("spin", 0, 12, 12.f);
    m_animator.play("spin");
}

void Coin::update(float dt)
{
    if (m_collected) return;
    m_animator.setFlipped(false);
    m_animator.update(dt);
}

void Coin::draw(sf::RenderWindow& window)
{
    if (m_collected) return;
    auto& sprite = m_animator.getSprite();
    sprite.setPosition(m_position);
    sprite.setOrigin({ 0.f, 0.f });
    sprite.setScale({ 2.f, 2.f });
    window.draw(sprite);
}

sf::FloatRect Coin::getBounds() const
{
    return sf::FloatRect(m_position, { 32.f, 32.f });
}