#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <optional>
#include <vector>
#include <memory>
#include "State.h"
#include "Player.h"
#include "Platform.h"
#include "Coin.h"
#include "Barrier.h"
#include "Bonfire.h"
#include "Animator.h"
#include "Paukich.h"
#include "Prizrak.h"
#include "Boss.h"

class Game;

class PlayState : public State
{
public:
    PlayState(Game& game, int level = 1);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    void resolveCollisions();
    void drawHud(sf::RenderWindow& window);
    void drawShopMenu(sf::RenderWindow& window);
    void setupLevel1();
    void setupLevel2();
    void setupLevel3();

    Game& m_game;
    int m_level = 1;
    sf::Texture m_bgTexture;
    std::optional<sf::Sprite> m_bgSprite;
    sf::Texture m_platformTexture;
    sf::Texture m_platformTexture2;
    sf::Texture m_bonfireTexture;
    std::optional<Bonfire> m_bonfire;
    bool m_transitioning = false;
    float m_transitionTimer = 0.f;
    sf::Texture m_playerTexture;
    sf::Texture m_attackTexture;
    sf::Texture m_arrowTexture;
    std::optional<Player> m_player;
    std::vector<Platform> m_platforms;
    sf::Texture m_bushTexture;
    sf::Texture m_treeTexture;
    std::vector<Barrier> m_barriers;
    sf::View m_camera;
    float m_levelWidth = 3840.f;
    sf::Texture m_paukich_texture;
    sf::Texture m_prizrak_texture;
    sf::Texture m_boss_texture;
    sf::Texture m_bossBarTex;
    sf::Sprite  m_bossBarBg;
    sf::Sprite  m_bossBarFill;
    Boss* m_bossPtr = nullptr;
    std::vector<std::unique_ptr<Enemy>> m_enemies;
    sf::Texture m_coinTexture;
    std::vector<std::unique_ptr<Coin>> m_coins;
    int m_coinCount = 0;
    sf::Font m_font;
    std::optional<sf::Text> m_coinText;
    int m_tutorialStep = 0;
    std::optional<sf::Text> m_tutorialText;

    // HUD
    sf::Texture m_hpBarTex;
    sf::Texture m_hpCrestTex;
    sf::Sprite  m_hpBarBg;
    sf::Sprite  m_hpBarFill;
    sf::Sprite  m_hpCrest;

    // Торговец
    sf::Texture m_traderTexture;
    std::optional<Animator> m_traderAnimator;
    sf::Vector2f m_traderPos;
    bool m_shopOpen = false;
    int m_potions = 0;
    static constexpr int   POTION_COST = 5;
    static constexpr int   POTION_HP = 1;
    static constexpr int   MAX_POTIONS = 3;
    static constexpr float TRADER_INTERACT_DIST = 150.f;
    std::optional<sf::Text> m_shopText;

    // Музыка
    sf::Music m_music;

    // Звуки
    sf::SoundBuffer m_coinSoundBuf;
    sf::SoundBuffer m_jumpSoundBuf;
    sf::SoundBuffer m_swordSoundBuf;
    sf::SoundBuffer m_arrowSoundBuf;
    std::optional<sf::Sound> m_coinSound;
};