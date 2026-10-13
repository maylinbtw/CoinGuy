#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"

class Game;

class MenuState : public State
{
public:
    MenuState(Game& game);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    Game& m_game;

    sf::Texture m_bgTex;
    sf::Texture m_logoTex;
    sf::Texture m_playTex;
    sf::Texture m_exitTex;

    sf::Sprite m_bg;
    sf::Sprite m_logo;
    sf::Sprite m_play;
    sf::Sprite m_exit;

    sf::Music m_music;

    int m_selected = 0;
};