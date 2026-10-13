#include "Prizrak.h"
#include <cmath>

Prizrak::Prizrak(sf::Texture& texture, float x, float y)
    : Enemy(texture, 31, 44, x, y)
    , m_patrolLeft(x - 250.f)
    , m_patrolRight(x + 250.f)
    , m_startY(y)
{
    m_animator.addAnimation("float", 0, 4, 8.f);
    m_animator.play("float");
    m_animator.setCustomScale(2.f);
    m_velocity.x = -m_speed;
}

void Prizrak::update(float dt)
{
    if (!m_alive) return;

    m_damageCooldown -= dt;
    m_floatTimer += dt;

    // плавное парение вверх-вниз
    m_position.y = m_startY + std::sin(m_floatTimer * 2.f) * 20.f;

    m_position.x += m_velocity.x * dt;

    if (m_position.x <= m_patrolLeft)
    {
        m_velocity.x = m_speed;
        m_facingRight = true;
    }
    else if (m_position.x >= m_patrolRight)
    {
        m_velocity.x = -m_speed;
        m_facingRight = false;
    }

    m_animator.setFlipped(m_facingRight);
    m_animator.update(dt);
}

bool Prizrak::canDamage()
{
    if (m_damageCooldown <= 0.f)
    {
        m_damageCooldown = 1.f;
        return true;
    }
    return false;
}