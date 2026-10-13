#pragma once
#include <SFML/Graphics.hpp>
#include "Animator.h"

class Coin
{
public:
    Coin(sf::Texture& texture, float x, float y);

    void update(float dt);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    bool isCollected() const { return m_collected; }
    void collect() { m_collected = true; }

private:
    Animator m_animator;
    sf::Vector2f m_position;
    bool m_collected = false;
};