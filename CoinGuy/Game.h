#pragma once
#include <SFML/Graphics.hpp>
#include "StateMachine.h"

class Game
{
public:
    Game();
    void run();

    sf::RenderWindow& getWindow() { return m_window; }
    StateMachine& getStateMachine() { return m_states; }
    int getTotalCoins() const { return m_totalCoins; }
    void addCoins(int amount) { m_totalCoins += amount; }

private:
    void handleEvents();
    void update(float dt);
    void draw();
    int m_totalCoins = 0;

    sf::RenderWindow m_window;
    StateMachine m_states;

    static constexpr float FIXED_STEP = 1.f / 60.f;
};