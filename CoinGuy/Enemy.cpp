#include "Enemy.h"

Enemy::Enemy(sf::Texture& texture, int frameW, int frameH, float x, float y)
    : m_animator(texture, frameW, frameH)
    , m_position(x, y)
{}

void Enemy::draw(sf::RenderWindow& window)
{
    auto& sprite = m_animator.getSprite();
    sprite.setPosition(m_position);
    window.draw(sprite);
}

sf::FloatRect Enemy::getBounds() const
{
    float w = (float)m_animator.getFrameWidth() * m_animator.getScale();
    float h = (float)m_animator.getFrameHeight() * m_animator.getScale();
    return sf::FloatRect(m_position, { w, h });
}

void Enemy::takeDamage(int dmg)
{
    m_hp -= dmg;
    if (m_hp <= 0)
        m_alive = false;
}