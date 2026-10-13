#include "Boss.h"
#include <cmath>

Boss::Boss(sf::Texture& texture, float x, float y)
    : Enemy(texture, 31, 44, x, y)
{
    m_animator.addAnimation("idle", 0, 1, 4.f);
    m_animator.play("idle");
    m_animator.setCustomScale(4.f);
    m_hp = MAX_BOSS_HP;
    m_velocity.x = -m_speed;
}

void Boss::update(float dt)
{
    if (!m_alive) return;

    m_damageCooldown -= dt;
    m_chargeTimer -= dt;

    float dx = m_playerPos.x - m_position.x;

    if (!m_charging && std::abs(dx) < CHARGE_RANGE && m_chargeTimer <= 0.f)
    {
        m_charging = true;
        m_velocity.x = (dx > 0 ? CHARGE_SPEED : -CHARGE_SPEED);
        m_chargeTimer = 2.f;
    }

    if (m_charging && m_chargeTimer <= 1.5f)
        m_charging = false;

    if (!m_charging)
    {
        m_velocity.x = (dx > 0 ? m_speed : -m_speed);
    }

    m_position.x += m_velocity.x * dt;
    m_position.x = std::max(m_position.x, 100.f);
    m_position.x = std::min(m_position.x, 3700.f);

    m_facingRight = m_velocity.x > 0;
    m_animator.setFlipped(!m_facingRight);
    m_animator.update(dt);
}

bool Boss::canDamage()
{
    if (m_damageCooldown <= 0.f)
    {
        m_damageCooldown = 0.8f;
        return true;
    }
    return false;
}