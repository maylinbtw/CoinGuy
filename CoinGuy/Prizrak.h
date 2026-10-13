#pragma once
#include "Enemy.h"

class Prizrak : public Enemy
{
public:
    Prizrak(sf::Texture& texture, float x, float y);
    void update(float dt) override;
    bool canDamage();

private:
    float m_patrolLeft;
    float m_patrolRight;
    float m_speed = 60.f;
    float m_damageCooldown = 0.f;
    float m_floatTimer = 0.f;
    float m_startY;
};