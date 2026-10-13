#include "Game.h"

Game::Game()
    : m_window(sf::VideoMode::getDesktopMode(), "CoinGuy", sf::Style::None)
{
    m_window.setFramerateLimit(60);
}

void Game::run()
{
    sf::Clock clock;
    float accumulator = 0.f;

    while (m_window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        if (dt > 0.1f) dt = 0.1f;
        accumulator += dt;

        handleEvents();

        while (accumulator >= FIXED_STEP)
        {
            if (m_states.current())
                m_states.current()->update(FIXED_STEP);
            accumulator -= FIXED_STEP;
        }

        m_states.applyPending();

        if (m_states.isEmpty())
            m_window.close();

        draw();
    }
}

void Game::handleEvents()
{
    while (auto event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            m_window.close();

        if (m_states.current())
            m_states.current()->handleEvent(*event);
    }
}

void Game::draw()
{
    m_window.clear(sf::Color(20, 20, 20));

    if (m_states.current())
        m_states.current()->draw(m_window);

    m_window.display();
}