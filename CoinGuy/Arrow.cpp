#include "Arrow.h"
#include <cmath>

Arrow::Arrow(sf::Texture& texture, float x, float y, bool goingRight)
    : m_sprite(texture)
    , m_position(x, y)
    , m_goingRight(goingRight)
{
    m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 57, 18 }));
    m_velocity = { goingRight ? SPEED : -SPEED, -100.f };
    m_sprite.setScale({ 0.5f, 0.5f });
}

void Arrow::update(float dt)
{
    if (!m_alive) return;

    m_velocity.y += GRAVITY * dt;
    m_position += m_velocity * dt;

    m_traveled += std::abs(m_velocity.x * dt);
    if (m_traveled >= MAX_RANGE || m_position.y > 800.f)
        m_alive = false;

    float angle = std::atan2(m_velocity.y, m_velocity.x) * 180.f / 3.14159f;
    m_sprite.setRotation(sf::degrees(angle));
    m_sprite.setScale({ 2.f, 2.f });
}

void Arrow::draw(sf::RenderWindow& window)
{
    if (!m_alive) return;
    m_sprite.setOrigin({ 28.5f, 9.f }); // центр спрайта для поворота
    m_sprite.setPosition(m_position);
    window.draw(m_sprite);
}

sf::FloatRect Arrow::getBounds() const
{
    return sf::FloatRect({ m_position.x - 28.f, m_position.y - 9.f }, { 57.f * 2.f, 18.f * 2.f });
}