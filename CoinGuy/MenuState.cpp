#include "MenuState.h"
#include "Game.h"
#include "PlayState.h"

MenuState::MenuState(Game& game)
    : m_game(game)
    , m_bg(m_bgTex)
    , m_logo(m_logoTex)
    , m_play(m_playTex)
    , m_exit(m_exitTex)
{
    m_bgTex.loadFromFile("assets/sprites/MenuUI/Fon.png");
    m_bg.setTexture(m_bgTex, true);
    m_bg.setScale({ 1366.f / 2560.f, 768.f / 1440.f });

    m_logoTex.loadFromFile("assets/sprites/MenuUI/Logo.png");
    m_logo.setTexture(m_logoTex, true);
    m_logo.setScale({ 0.35f, 0.35f });
    m_logo.setPosition({ 683.f - (2560.f * 0.35f) / 2.f, 30.f });

    m_playTex.loadFromFile("assets/sprites/MenuUI/Igrats.png");
    m_play.setTexture(m_playTex, true);
    m_play.setScale({ 0.6f, 0.6f });
    m_play.setPosition({ 683.f - 120.f, 500.f });

    m_exitTex.loadFromFile("assets/sprites/MenuUI/Vykhod.png");
    m_exit.setTexture(m_exitTex, true);
    m_exit.setScale({ 0.25f, 0.25f });
    m_exit.setPosition({ 1170.f, 600.f });

    m_music.openFromFile("assets/sounds/Main_Menu.mp3");
    m_music.setLooping(true);
    m_music.setVolume(50.f);
    m_music.play();
}

void MenuState::handleEvent(const sf::Event& event)
{
    if (auto* key = event.getIf<sf::Event::KeyPressed>())
    {
        if (key->code == sf::Keyboard::Key::Up)
            m_selected = 0;
        else if (key->code == sf::Keyboard::Key::Down)
            m_selected = 1;
        else if (key->code == sf::Keyboard::Key::Enter)
        {
            if (m_selected == 0)
                m_game.getStateMachine().change(std::make_unique<PlayState>(m_game));
            else
                m_game.getWindow().close();
        }
    }
}

void MenuState::update(float dt)
{
    m_play.setColor(m_selected == 0 ? sf::Color::White : sf::Color(180, 180, 180));
    m_exit.setColor(m_selected == 1 ? sf::Color::White : sf::Color(180, 180, 180));
}

void MenuState::draw(sf::RenderWindow& window)
{
    window.draw(m_bg);
    window.draw(m_logo);
    window.draw(m_play);
    window.draw(m_exit);
}