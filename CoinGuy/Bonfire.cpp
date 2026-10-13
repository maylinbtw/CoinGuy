#include "Bonfire.h"

Bonfire::Bonfire(sf::Texture& texture, float x, float y)
    : m_animator(texture, 64, 44)
    , m_position(x, y)
{
    m_animator.addAnimation("burn", 0, 4, 8.f);
    m_animator.play("burn");
    m_animator.setCustomScale(2.f);
}

void Bonfire::update(float dt)
{
    m_animator.update(dt);
}

void Bonfire::draw(sf::RenderWindow& window)
{
    auto& sprite = m_animator.getSprite();
    sprite.setPosition(m_position);
    window.draw(sprite);
}

sf::FloatRect Bonfire::getBounds() const
{
    return sf::FloatRect({ m_position.x + 20.f, m_position.y }, { 88.f, 88.f });
}