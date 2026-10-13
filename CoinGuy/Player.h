#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <optional>
#include <vector>
#include "Animator.h"
#include "Arrow.h"

class Player
{
public:
    Player(sf::Texture& texture);

    void handleEvent(const sf::Event& event);
    void update(float dt);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    sf::FloatRect getAttackBounds() const;
    sf::Vector2f getPosition() const { return m_position; }
    void setPosition(sf::Vector2f pos) { m_position = pos; }

    void onLand();
    bool isOnGround() const { return m_onGround; }
    void setOnGround(bool v) { m_onGround = v; }
    void setVelocityY(float vy) { m_velocity.y = vy; }
    float getVelocityY() const { return m_velocity.y; }
    bool isAttacking() const { return m_attacking; }

    void updateAnimationPublic();
    void animatorUpdate(float dt);
    void setAttackTexture(sf::Texture& tex);
    void setArrowTexture(sf::Texture& tex);

    void setJumpSound(sf::SoundBuffer& buf) { m_jumpBuf = buf; m_jumpSound.setBuffer(m_jumpBuf); }
    void setSwordSound(sf::SoundBuffer& buf) { m_swordBuf = buf; m_swordSound.setBuffer(m_swordBuf); }
    void setArrowSound(sf::SoundBuffer& buf) { m_arrowBuf = buf; m_arrowSound.setBuffer(m_arrowBuf); }

    bool hasMoved() const { return m_hasMoved; }
    bool hasJumped() const { return m_hasJumped; }
    bool hasAttacked() const { return m_hasAttacked; }
    bool hasSprinted() const { return m_hasSprinted; }

    int  getHp() const { return m_hp; }
    int  getMaxHp() const { return MAX_HP; }
    void takeDamage(int dmg);
    bool isDead() const { return m_hp <= 0; }
    bool hasAttackHit() const { return m_attackHit; }
    void setAttackHit(bool v) { m_attackHit = v; }

    std::vector<Arrow>& getArrows() { return m_arrows; }

private:
    void updateAnimation();

    Animator m_animator;
    std::optional<Animator> m_attackAnimator;
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;

    bool m_onGround = false;
    bool m_jumpHeld = false;
    float m_jumpTimer = 0.f;
    int m_jumpsLeft = 2;
    bool m_facingRight = true;
    bool m_attacking = false;
    bool m_attackHit = false;
    float m_attackTimer = 0.f;

    bool m_hasMoved = false;
    bool m_hasJumped = false;
    bool m_hasAttacked = false;
    bool m_hasSprinted = false;

    int m_hp = 5;
    sf::Texture* m_arrowTex = nullptr;
    std::vector<Arrow> m_arrows;
    bool m_bowCooldown = false;
    float m_bowCooldownTimer = 0.f;

    sf::SoundBuffer m_jumpBuf;
    sf::SoundBuffer m_swordBuf;
    sf::SoundBuffer m_arrowBuf;
    sf::Sound m_jumpSound{ m_jumpBuf };
    sf::Sound m_swordSound{ m_swordBuf };
    sf::Sound m_arrowSound{ m_arrowBuf };

    static constexpr int   MAX_HP = 5;
    static constexpr float SPEED = 200.f;
    static constexpr float SPRINT_MULT = 2.f;
    static constexpr float JUMP_FORCE = -350.f;
    static constexpr float HOLD_FORCE = -200.f;
    static constexpr float MAX_JUMP_TIME = 0.25f;
    static constexpr float GRAVITY = 1200.f;
    static constexpr float MAX_FALL = 800.f;
    static constexpr float ATTACK_DURATION = 0.3f;
    static constexpr float BOW_COOLDOWN = 0.5f;
};