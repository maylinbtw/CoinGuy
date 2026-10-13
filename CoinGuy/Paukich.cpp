#include "Paukich.h"
#include <cmath>

Paukich::Paukich(sf::Texture& texture, float x, float y)
    : Enemy(texture, 221, 120, x, y)
    , m_patrolLeft(x - 200.f)
    , m_patrolRight(x + 200.f)
{
    m_animator.addAnimation("idle", 0, 6, 8.f);
    m_animator.addAnimation("walk", 120, 8, 10.f);
    m_animator.addAnimation("run", 240, 8, 12.f);
    m_animator.addAnimation("attack", 360, 6, 10.f);
    m_animator.play("walk");
    m_animator.setCustomScale(0.5f);
    m_velocity.x = -m_speed;
}

void Paukich::update(float dt)
{
    if (!m_alive) return;

    m_damageCooldown -= dt;

    float dx = m_playerPos.x - m_position.x;
    bool playerNear = std::abs(dx) < ATTACK_RANGE;

    if (playerNear)
    {
        m_velocity.x = 0.f;
        m_animator.play("attack");
        m_facingRight = dx > 0;
    }
    else
    {
        // восстанавливаем скорость если остановился
        if (m_velocity.x == 0.f)
            m_velocity.x = -m_speed;

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

        m_animator.play("walk");
    }

    m_animator.setFlipped(!m_facingRight);
    m_animator.update(dt);
}

bool Paukich::canDamage()
{
    if (m_damageCooldown <= 0.f)
    {
        m_damageCooldown = 1.f;
        return true;
    }
    return false;
}