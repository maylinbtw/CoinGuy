#pragma once
#include "Enemy.h"

class Paukich : public Enemy
{
public:
    Paukich(sf::Texture& texture, float x, float y);
    void update(float dt) override;
    bool canDamage();
    void setPlayerPos(sf::Vector2f pos) { m_playerPos = pos; }

private:
    float m_patrolLeft;
    float m_patrolRight;
    float m_speed = 80.f;
    float m_damageCooldown = 0.f;
    sf::Vector2f m_playerPos;
    static constexpr float ATTACK_RANGE = 80.f;
};