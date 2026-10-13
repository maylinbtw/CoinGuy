#include "PlayState.h"
#include "Game.h"
#include "MenuState.h"
#include <algorithm>
#include <cmath>

PlayState::PlayState(Game& game, int level)
    : m_game(game)
    , m_level(level)
    , m_hpBarBg(m_hpBarTex)
    , m_hpBarFill(m_hpBarTex)
    , m_hpCrest(m_hpCrestTex)
    , m_bossBarBg(m_bossBarTex)
    , m_bossBarFill(m_bossBarTex)
{
    if (m_level == 1)
        m_game.addCoins(-m_game.getTotalCoins()); // сброс
    m_coinCount = m_game.getTotalCoins();

    m_platformTexture.loadFromFile("assets/sprites/Platforms/Base_platform.png");
    m_playerTexture.loadFromFile("assets/sprites/Characters/Knight.png");
    m_player.emplace(m_playerTexture);
    m_attackTexture.loadFromFile("assets/sprites/Characters/CoinGuy_Attack-Sheet.png");
    m_player->setAttackTexture(m_attackTexture);
    m_arrowTexture.loadFromFile("assets/sprites/Weapons/arrow.png");
    m_player->setArrowTexture(m_arrowTexture);

    m_jumpSoundBuf.loadFromFile("assets/sounds/Jump.mp3");
    m_swordSoundBuf.loadFromFile("assets/sounds/Sword_Attack.mp3");
    m_arrowSoundBuf.loadFromFile("assets/sounds/Arrow_Attack.mp3");
    m_coinSoundBuf.loadFromFile("assets/sounds/Coin_Received.mp3");
    m_coinSound.emplace(m_coinSoundBuf);
    m_player->setJumpSound(m_jumpSoundBuf);
    m_player->setSwordSound(m_swordSoundBuf);
    m_player->setArrowSound(m_arrowSoundBuf);

    m_coinTexture.loadFromFile("assets/sprites/Coins/Coin.png");
    m_bonfireTexture.loadFromFile("assets/sprites/Bonfire/Bonfire_sheet.png");
    m_bushTexture.loadFromFile("assets/sprites/Barriers/bush.png");
    m_treeTexture.loadFromFile("assets/sprites/Barriers/tree.png");
    m_paukich_texture.loadFromFile("assets/sprites/Enemies/Paukich/Paukich_sheet.png");

    m_traderTexture.loadFromFile("assets/sprites/Trader/trader_sheet.png");
    m_traderAnimator.emplace(m_traderTexture, 128, 128);
    m_traderAnimator->addAnimation("idle", 0, 6, 8.f);
    m_traderAnimator->addAnimation("dialogue", 128, 16, 10.f);
    m_traderAnimator->play("idle");
    m_traderAnimator->setCustomScale(1.5f);

    m_font.openFromFile("assets/fonts/PressStart2P.ttf");

    m_coinText.emplace(m_font, sf::String(L"Монет: " + std::to_wstring(m_coinCount)), 24);
    m_coinText->setFillColor(sf::Color::Yellow);
    m_coinText->setPosition({ 700.f, 20.f });

    m_tutorialText.emplace(m_font, sf::String(L"Используй \u2190 \u2192 для движения"), 28);
    m_tutorialText->setFillColor(sf::Color::White);
    m_tutorialText->setOutlineColor(sf::Color::Black);
    m_tutorialText->setOutlineThickness(2.f);
    m_tutorialText->setPosition({ 400.f, 80.f });

    m_shopText.emplace(m_font, sf::String(L""), 16);
    m_shopText->setFillColor(sf::Color::White);
    m_shopText->setOutlineColor(sf::Color::Black);
    m_shopText->setOutlineThickness(2.f);

    m_hpBarTex.loadFromFile("assets/sprites/UI/Gradient_HP.png");
    m_hpCrestTex.loadFromFile("assets/sprites/UI/Health_Crest.png");
    m_hpBarBg.setTexture(m_hpBarTex, true);
    m_hpBarBg.setTextureRect(sf::IntRect({ 0, 111 }, { 1000, 111 }));
    m_hpBarBg.setScale({ 0.3f, 0.3f });
    m_hpBarBg.setPosition({ 60.f, 20.f });
    m_hpBarFill.setTexture(m_hpBarTex, true);
    m_hpBarFill.setTextureRect(sf::IntRect({ 0, 0 }, { 1000, 111 }));
    m_hpBarFill.setScale({ 0.3f, 0.3f });
    m_hpBarFill.setPosition({ 60.f, 20.f });
    m_hpCrest.setTexture(m_hpCrestTex, true);
    m_hpCrest.setScale({ 0.08f, 0.08f });
    m_hpCrest.setPosition({ 10.f, 16.f });

    if (m_level == 1)      setupLevel1();
    else if (m_level == 2) setupLevel2();
    else                   setupLevel3();

    m_camera = sf::View(sf::FloatRect({ 0.f, 0.f }, { 1366.f, 768.f }));
}

void PlayState::setupLevel1()
{
    m_bgTexture.loadFromFile("assets/sprites/Backgrounds/Forest.png");
    m_bgSprite.emplace(m_bgTexture);

    m_barriers.emplace_back(m_treeTexture, 350.f, 560.f, 1.f);
    m_barriers.emplace_back(m_treeTexture, 900.f, 560.f, 1.f);
    m_barriers.emplace_back(m_treeTexture, 1600.f, 560.f, 1.f);
    m_barriers.emplace_back(m_treeTexture, 2400.f, 560.f, 1.f);
    m_barriers.emplace_back(m_treeTexture, 3200.f, 560.f, 1.f);
    m_barriers.emplace_back(m_bushTexture, 550.f, 640.f, 2.5f);
    m_barriers.emplace_back(m_bushTexture, 1100.f, 640.f, 2.5f);
    m_barriers.emplace_back(m_bushTexture, 1850.f, 640.f, 2.5f);
    m_barriers.emplace_back(m_bushTexture, 2700.f, 640.f, 2.5f);

    m_coins.reserve(10);
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 300.f, 660.f));
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 650.f, 600.f));
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 1000.f, 660.f));
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 1500.f, 580.f));
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 2000.f, 660.f));
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 2400.f, 600.f));
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 2800.f, 660.f));
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 3200.f, 580.f));

    for (int i = 0; i < 12; i++)
        m_platforms.emplace_back(m_platformTexture, i * 347.f, 700.f, 347.f, 30.f);

    m_enemies.push_back(std::make_unique<Paukich>(m_paukich_texture, 600.f, 650.f));
    m_enemies.push_back(std::make_unique<Paukich>(m_paukich_texture, 1400.f, 650.f));
    m_enemies.push_back(std::make_unique<Paukich>(m_paukich_texture, 2200.f, 650.f));

    m_bonfire.emplace(m_bonfireTexture, 3600.f, 620.f);
    m_traderPos = { 1800.f, 550.f };

    m_music.openFromFile("assets/sounds/Mysterious_Forest.mp3");
    m_music.setLooping(true);
    m_music.setVolume(50.f);
    m_music.play();
}

void PlayState::setupLevel2()
{
    m_bgTexture.loadFromFile("assets/sprites/Backgrounds/Forest_night.png");
    m_bgSprite.emplace(m_bgTexture);

    m_coins.reserve(10);
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 400.f, 660.f));
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 700.f, 590.f));
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 1200.f, 660.f));
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 1600.f, 600.f));
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 2000.f, 660.f));
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 2400.f, 580.f));
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 2800.f, 660.f));
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 3200.f, 600.f));

    for (int i = 0; i < 12; i++)
        m_platforms.emplace_back(m_platformTexture, i * 347.f, 700.f, 347.f, 30.f);

    m_enemies.push_back(std::make_unique<Paukich>(m_paukich_texture, 500.f, 650.f));
    m_enemies.push_back(std::make_unique<Paukich>(m_paukich_texture, 1300.f, 650.f));
    m_enemies.push_back(std::make_unique<Paukich>(m_paukich_texture, 2100.f, 650.f));

    m_prizrak_texture.loadFromFile("assets/sprites/Enemies/Prizrak/Prizrak_sheet.png");
    m_enemies.push_back(std::make_unique<Prizrak>(m_prizrak_texture, 900.f, 580.f));
    m_enemies.push_back(std::make_unique<Prizrak>(m_prizrak_texture, 1800.f, 580.f));
    m_enemies.push_back(std::make_unique<Prizrak>(m_prizrak_texture, 2900.f, 580.f));

    m_bonfire.emplace(m_bonfireTexture, 3600.f, 620.f);
    m_traderPos = { 2200.f, 550.f };

    m_music.openFromFile("assets/sounds/Blackroot_Hunt.mp3");
    m_music.setLooping(true);
    m_music.setVolume(50.f);
    m_music.play();
}

void PlayState::setupLevel3()
{
    m_bgTexture.loadFromFile("assets/sprites/Backgrounds/Sunset.png");
    m_bgSprite.emplace(m_bgTexture);

    m_coins.reserve(5);
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 500.f, 660.f));
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 1000.f, 590.f));
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 1500.f, 660.f));
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 2500.f, 600.f));
    m_coins.push_back(std::make_unique<Coin>(m_coinTexture, 3000.f, 660.f));

    for (int i = 0; i < 12; i++)
        m_platforms.emplace_back(m_platformTexture, i * 347.f, 700.f, 347.f, 30.f);

    m_boss_texture.loadFromFile("assets/sprites/Enemies/Boss/Golova_Ksarana.png");
    auto boss = std::make_unique<Boss>(m_boss_texture, 2000.f, 620.f);
    m_bossPtr = boss.get();
    m_enemies.push_back(std::move(boss));

    m_bossBarTex.loadFromFile("assets/sprites/UI/Slaydery_Bossa.png");
    m_bossBarBg.setTexture(m_bossBarTex, true);
    m_bossBarBg.setTextureRect(sf::IntRect({ 0, 111 }, { 1000, 111 }));
    m_bossBarBg.setScale({ 0.8f, 0.4f });
    m_bossBarBg.setPosition({ 183.f, 720.f });
    m_bossBarFill.setTexture(m_bossBarTex, true);
    m_bossBarFill.setTextureRect(sf::IntRect({ 0, 0 }, { 1000, 111 }));
    m_bossBarFill.setScale({ 0.8f, 0.4f });
    m_bossBarFill.setPosition({ 183.f, 720.f });

    m_bonfire.emplace(m_bonfireTexture, 3600.f, 620.f);
    m_traderPos = { 800.f, 550.f };

    m_music.openFromFile("assets/sounds/Blood_at_Dusk.mp3");
    m_music.setLooping(true);
    m_music.setVolume(50.f);
    m_music.play();
}

void PlayState::handleEvent(const sf::Event& event)
{
    if (auto* key = event.getIf<sf::Event::KeyPressed>())
    {
        if (key->code == sf::Keyboard::Key::Escape)
            m_game.getStateMachine().change(std::make_unique<MenuState>(m_game));

        if (key->code == sf::Keyboard::Key::E)
        {
            float dx = m_player->getPosition().x - m_traderPos.x;
            if (std::abs(dx) < TRADER_INTERACT_DIST)
            {
                m_shopOpen = !m_shopOpen;
                if (m_shopOpen)
                {
                    m_traderAnimator->setLooping(false);
                    m_traderAnimator->play("dialogue");
                }
                else
                {
                    m_traderAnimator->setLooping(true);
                    m_traderAnimator->play("idle");
                }
            }
        }

        if (m_shopOpen && key->code == sf::Keyboard::Key::B)
        {
            if (m_potions < MAX_POTIONS && m_coinCount >= POTION_COST)
            {
                m_coinCount -= POTION_COST;
                m_game.addCoins(-POTION_COST);
                m_potions++;
            }
        }

        if (key->code == sf::Keyboard::Key::F && m_potions > 0)
        {
            m_potions--;
            m_player->takeDamage(-POTION_HP);
        }
    }

    m_player->handleEvent(event);
}

void PlayState::update(float dt)
{
    m_player->update(dt);
    resolveCollisions();
    m_player->updateAnimationPublic();
    m_player->animatorUpdate(dt);

    if (m_player->isDead())
    {
        m_game.getStateMachine().change(std::make_unique<MenuState>(m_game));
        return;
    }

    float camX = m_player->getPosition().x + 40.f;
    camX = std::max(camX, 640.f);
    camX = std::min(camX, m_levelWidth - 640.f);
    m_camera.setCenter({ camX, 360.f });

    for (auto& e : m_enemies)
    {
        auto* p = dynamic_cast<Paukich*>(e.get());
        if (p) p->setPlayerPos(m_player->getPosition());
        auto* b = dynamic_cast<Boss*>(e.get());
        if (b) b->setPlayerPos(m_player->getPosition());
        e->update(dt);
    }

    for (auto& e : m_enemies)
    {
        if (!e->isAlive()) continue;

        auto* p = dynamic_cast<Paukich*>(e.get());
        if (p)
        {
            float dx = std::abs(m_player->getPosition().x - e->getBounds().position.x);
            float dy = std::abs(m_player->getPosition().y - e->getBounds().position.y);
            if (dx < 80.f && dy < 60.f && p->canDamage())
                m_player->takeDamage(1);
        }

        auto* pr = dynamic_cast<Prizrak*>(e.get());
        if (pr)
        {
            float dx = std::abs(m_player->getPosition().x - e->getBounds().position.x);
            float dy = std::abs(m_player->getPosition().y - e->getBounds().position.y);
            if (dx < 60.f && dy < 50.f && pr->canDamage())
                m_player->takeDamage(1);
        }

        auto* b = dynamic_cast<Boss*>(e.get());
        if (b)
        {
            float dx = std::abs(m_player->getPosition().x - e->getBounds().position.x);
            float dy = std::abs(m_player->getPosition().y - e->getBounds().position.y);
            if (dx < 80.f && dy < 60.f && b->canDamage())
                m_player->takeDamage(1);
        }
    }

    if (m_player->isAttacking() && !m_player->hasAttackHit())
    {
        for (auto& e : m_enemies)
        {
            if (!e->isAlive()) continue;
            if (m_player->getAttackBounds().findIntersection(e->getBounds()))
            {
                e->takeDamage(1);
                m_player->setAttackHit(true);
                break;
            }
        }
    }

    for (auto& a : m_player->getArrows())
    {
        if (!a.isAlive() || a.hasHit()) continue;
        for (auto& e : m_enemies)
        {
            if (!e->isAlive()) continue;
            if (a.getBounds().findIntersection(e->getBounds()))
            {
                e->takeDamage(1);
                a.markHit();
                break;
            }
        }
    }

    if (m_bonfire)
    {
        m_bonfire->update(dt);
        if (m_player->getBounds().findIntersection(m_bonfire->getBounds()))
            m_transitioning = true;
    }

    if (m_transitioning)
    {
        m_transitionTimer += dt;
        if (m_transitionTimer >= 1.f)
        {
            if (m_level < 3)
                m_game.getStateMachine().change(std::make_unique<PlayState>(m_game, m_level + 1));
            else
                m_game.getStateMachine().change(std::make_unique<MenuState>(m_game));
        }
    }

    for (auto& c : m_coins)
    {
        c->update(dt);
        if (!c->isCollected() && m_player->getBounds().findIntersection(c->getBounds()))
        {
            c->collect();
            m_coinCount++;
            m_game.addCoins(1);
            if (m_coinSound) m_coinSound->play();
        }
    }
    m_coinText->setString(sf::String(L"Монет: " + std::to_wstring(m_coinCount)));

    m_traderAnimator->update(dt);

    if (m_shopOpen)
    {
        float dx = m_player->getPosition().x - m_traderPos.x;
        if (std::abs(dx) >= TRADER_INTERACT_DIST)
        {
            m_shopOpen = false;
            m_traderAnimator->setLooping(true);
            m_traderAnimator->play("idle");
        }
    }

    if (m_tutorialStep == 0 && m_player->hasMoved())
    {
        m_tutorialStep = 1;
        m_tutorialText->setString(sf::String(L"Нажми \u2191 для прыжка"));
    }
    else if (m_tutorialStep == 1 && m_player->hasJumped())
    {
        m_tutorialStep = 2;
        m_tutorialText->setString(sf::String(L"Нажми Z для атаки"));
    }
    else if (m_tutorialStep == 2 && m_player->hasAttacked())
    {
        m_tutorialStep = 3;
        m_tutorialText->setString(sf::String(L"Зажми Shift для спринта"));
    }
    else if (m_tutorialStep == 3 && m_player->hasSprinted())
    {
        m_tutorialStep = 4;
    }
    else if (m_tutorialStep == 4)
    {
        m_tutorialText->setString(sf::String(L"Нажми C для стрельбы"));
        m_tutorialStep = 5;
    }
    else if (m_tutorialStep == 5 && !m_player->getArrows().empty())
    {
        m_tutorialStep = 6;
        m_tutorialText->setString(sf::String(L"Нажми E у торговца для покупки"));
    }
    else if (m_tutorialStep == 6 && m_shopOpen)
    {
        m_tutorialStep = 7;
        m_tutorialText->setString(sf::String(L"[B] купить зелье, [F] выпить"));
    }
    else if (m_tutorialStep == 7 && m_potions > 0)
    {
        m_tutorialStep = 8;
    }
}

void PlayState::resolveCollisions()
{
    for (auto& plat : m_platforms)
    {
        sf::FloatRect pb = m_player->getBounds();
        sf::FloatRect platB = plat.getBounds();

        if (pb.findIntersection(platB))
        {
            float playerBottom = pb.position.y + pb.size.y;
            float platTop = platB.position.y;

            if (playerBottom > platTop && m_player->getVelocityY() >= 0.f)
            {
                sf::Vector2f pos = m_player->getPosition();
                m_player->setPosition({ pos.x, platTop - pb.size.y + 20.f });
                m_player->onLand();
            }
        }
    }
}

void PlayState::drawShopMenu(sf::RenderWindow& window)
{
    sf::RectangleShape bg({ 400.f, 150.f });
    bg.setFillColor(sf::Color(0, 0, 0, 180));
    bg.setOutlineColor(sf::Color::Yellow);
    bg.setOutlineThickness(2.f);
    bg.setPosition({ 483.f, 280.f });
    window.draw(bg);

    sf::Text t(m_font, sf::String(L"ТОРГОВЕЦ"), 20);
    t.setFillColor(sf::Color::Yellow);
    t.setPosition({ 530.f, 295.f });
    window.draw(t);

    sf::Text t2(m_font, sf::String(
        L"[B] Купить зелье - 5 монет\n"
        L"[F] Выпить зелье (+1 HP)\n"
        L"Зелий: " + std::to_wstring(m_potions) + L"/3\n"
        L"Монет: " + std::to_wstring(m_coinCount)
    ), 14);
    t2.setFillColor(sf::Color::White);
    t2.setPosition({ 493.f, 325.f });
    window.draw(t2);
}

void PlayState::drawHud(sf::RenderWindow& window)
{
    float ratio = (float)m_player->getHp() / m_player->getMaxHp();
    m_hpBarFill.setTextureRect(sf::IntRect({ 0, 0 }, { (int)(1000 * ratio), 111 }));
    window.draw(m_hpBarBg);
    window.draw(m_hpBarFill);
    window.draw(m_hpCrest);

    if (m_level == 3 && m_bossPtr && m_bossPtr->isAlive())
    {
        float ratio2 = (float)m_bossPtr->getHp() / m_bossPtr->getMaxHp();
        m_bossBarFill.setTextureRect(sf::IntRect({ 0, 0 }, { (int)(1000 * ratio2), 111 }));
        window.draw(m_bossBarBg);
        window.draw(m_bossBarFill);
    }
}

void PlayState::draw(sf::RenderWindow& window)
{
    window.setView(m_camera);
    float bgW = m_bgTexture.getSize().x;
    float bgH = m_bgTexture.getSize().y;
    int tilesX = (int)(m_levelWidth / bgW) + 2;
    for (int y = 0; y < 2; y++)
        for (int x = 0; x < tilesX; x++)
        {
            m_bgSprite->setPosition({ x * bgW, (float)y * bgH - bgH });
            window.draw(*m_bgSprite);
        }
    for (auto& p : m_platforms)
        p.draw(window);
    for (auto& e : m_enemies)
        if (e->isAlive())
            e->draw(window);
    for (auto& b : m_barriers)
        b.draw(window);
    for (auto& c : m_coins)
        c->draw(window);
    if (m_bonfire)
        m_bonfire->draw(window);

    auto& ts = m_traderAnimator->getSprite();
    ts.setPosition(m_traderPos);
    window.draw(ts);

    m_player->draw(window);

    window.setView(window.getDefaultView());
    drawHud(window);
    window.draw(*m_coinText);
    if (m_tutorialStep < 8)
        window.draw(*m_tutorialText);
    if (m_shopOpen)
        drawShopMenu(window);

    std::wstring potStr = L"Зелья: " + std::to_wstring(m_potions) + L"/3  [F] - выпить";
    m_shopText->setString(sf::String(potStr));
    m_shopText->setPosition({ 20.f, 55.f });
    window.draw(*m_shopText);
}