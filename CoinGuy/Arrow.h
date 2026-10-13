#pragma once
#include <SFML/Graphics.hpp>

class Arrow
{
public:
    Arrow(sf::Texture& texture, float x, float y, bool goingRight);

    void update(float dt);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    bool isAlive() const { return m_alive; }
    bool hasHit() const { return m_hasHit; }
    void markHit() { m_hasHit = true; m_alive = false; }

private:
    sf::Sprite m_sprite;
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    bool m_goingRight;
    bool m_alive = true;
    bool m_hasHit = false;

    static constexpr float SPEED = 500.f;
    static constexpr float GRAVITY = 400.f;
    static constexpr float MAX_RANGE = 1000.f;
    float m_traveled = 0.f;
};