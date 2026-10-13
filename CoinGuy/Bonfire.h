#pragma once
#include <SFML/Graphics.hpp>
#include "Animator.h"

class Bonfire
{
public:
    Bonfire(sf::Texture& texture, float x, float y);

    void update(float dt);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;

private:
    Animator m_animator;
    sf::Vector2f m_position;
};