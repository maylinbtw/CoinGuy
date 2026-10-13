#pragma once
#include "Enemy.h"

class Boss : public Enemy
{
public:
    Boss(sf::Texture& texture, float x, float y);
    void update(float dt) override;
    bool canDamage();
    int getMaxHp() const { return MAX_BOSS_HP; }

private:
    float m_speed = 100.f;
    float m_damageCooldown = 0.f;
    sf::Vector2f m_playerPos;
    float m_chargeTimer = 0.f;
    bool m_charging = false;
    static constexpr int   MAX_BOSS_HP = 15;
    static constexpr float CHARGE_RANGE = 400.f;
    static constexpr float CHARGE_SPEED = 300.f;

public:
    void setPlayerPos(sf::Vector2f pos) { m_playerPos = pos; }
    int getHp() const { return m_hp; }
};