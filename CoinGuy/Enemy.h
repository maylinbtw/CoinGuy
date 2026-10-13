#pragma once
#include <SFML/Graphics.hpp>
#include "Animator.h"

class Enemy
{
public:
    Enemy(sf::Texture& texture, int frameW, int frameH, float x, float y);
    virtual ~Enemy() = default;

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    bool isAlive() const { return m_alive; }
    void takeDamage(int dmg);

protected:
    Animator m_animator;
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    float m_scale = 2.f;
    bool m_alive = true;
    bool m_facingRight = false;
    int m_hp = 3;
};