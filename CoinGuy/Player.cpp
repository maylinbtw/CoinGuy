#include "Player.h"
#include <cmath>
#include <algorithm>

Player::Player(sf::Texture& texture)
    : m_animator(texture, 32, 19)
{
    m_animator.addAnimation("idle", 9, 4, 8.f);
    m_animator.addAnimation("run", 73, 8, 12.f);
    m_animator.addAnimation("jump", 105, 8, 10.f);
    m_animator.addAnimation("fall", 169, 8, 8.f);
    m_animator.addAnimation("hit", 201, 4, 10.f);
    m_animator.addAnimation("death", 233, 4, 6.f);

    m_animator.play("idle");
    m_position = { 200.f, 480.f };
}

void Player::setAttackTexture(sf::Texture& tex)
{
    m_attackAnimator.emplace(tex, 37, 38);
    m_attackAnimator->addAnimation("attack", 0, 2, 10.f);
}

void Player::setArrowTexture(sf::Texture& tex)
{
    m_arrowTex = &tex;
}

void Player::takeDamage(int dmg)
{
    m_hp -= dmg;
    if (m_hp < 0) m_hp = 0;
    if (m_hp > MAX_HP) m_hp = MAX_HP;
}

void Player::handleEvent(const sf::Event& event)
{
    if (auto* key = event.getIf<sf::Event::KeyPressed>())
    {
        if (key->code == sf::Keyboard::Key::Up)
        {
            if (m_jumpsLeft > 0)
            {
                m_velocity.y = JUMP_FORCE;
                m_jumpSound.play();
                m_jumpHeld = true;
                m_jumpTimer = MAX_JUMP_TIME;
                m_jumpsLeft--;
                m_onGround = false;
                m_hasJumped = true;
            }
        }
        if (key->code == sf::Keyboard::Key::Z)
        {
            if (!m_attacking && m_attackAnimator)
            {
                m_attacking = true;
                m_attackHit = false;
                m_swordSound.play();
                m_attackTimer = ATTACK_DURATION;
                m_attackAnimator->play("attack");
                m_hasAttacked = true;
            }
        }
        if (key->code == sf::Keyboard::Key::C)
        {
            if (!m_bowCooldown && m_arrowTex)
            {
                float ax = m_facingRight ? m_position.x + 60.f : m_position.x;
                m_arrows.emplace_back(*m_arrowTex, ax, m_position.y, m_facingRight);
                m_arrowSound.play();
                m_bowCooldown = true;
                m_bowCooldownTimer = BOW_COOLDOWN;
            }
        }
    }

    if (auto* key = event.getIf<sf::Event::KeyReleased>())
    {
        if (key->code == sf::Keyboard::Key::Up)
            m_jumpHeld = false;
    }
}

void Player::update(float dt)
{
    m_onGround = false;

    float speed = SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
    {
        speed *= SPRINT_MULT;
        m_hasSprinted = true;
    }

    m_velocity.x = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        m_velocity.x = -speed;
        m_facingRight = false;
        m_hasMoved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        m_velocity.x = speed;
        m_facingRight = true;
        m_hasMoved = true;
    }

    if (m_jumpHeld && m_jumpTimer > 0.f)
    {
        m_velocity.y += HOLD_FORCE * dt;
        m_jumpTimer -= dt;
    }
    else
    {
        m_jumpHeld = false;
    }

    if (!m_onGround)
    {
        m_velocity.y += GRAVITY * dt;
        if (m_velocity.y > MAX_FALL)
            m_velocity.y = MAX_FALL;
    }

    m_position += m_velocity * dt;

    if (m_position.x < 0.f)
        m_position.x = 0.f;
    if (m_position.x > 3840.f - 32.f * 2.0f)
        m_position.x = 3840.f - 32.f * 2.0f;

    if (m_attacking)
    {
        m_attackTimer -= dt;
        if (m_attackTimer <= 0.f)
            m_attacking = false;
        if (m_attackAnimator)
        {
            m_attackAnimator->update(dt);
            m_attackAnimator->setFlipped(!m_facingRight);
        }
    }

    if (m_bowCooldown)
    {
        m_bowCooldownTimer -= dt;
        if (m_bowCooldownTimer <= 0.f)
            m_bowCooldown = false;
    }

    for (auto& a : m_arrows)
        a.update(dt);
    m_arrows.erase(
        std::remove_if(m_arrows.begin(), m_arrows.end(),
            [](const Arrow& a) { return !a.isAlive(); }),
        m_arrows.end());

    m_animator.setFlipped(!m_facingRight);
}

void Player::updateAnimation()
{
    if (!m_onGround)
    {
        if (m_velocity.y < 0.f)
            m_animator.play("jump");
        else
            m_animator.play("fall");
    }
    else if (std::abs(m_velocity.x) > 1.f)
        m_animator.play("run");
    else
        m_animator.play("idle");
}

void Player::updateAnimationPublic()
{
    updateAnimation();
}

void Player::animatorUpdate(float dt)
{
    m_animator.update(dt);
}

void Player::onLand()
{
    m_onGround = true;
    m_jumpsLeft = 2;
    m_velocity.y = 0.f;
}

void Player::draw(sf::RenderWindow& window)
{
    for (auto& a : m_arrows)
        a.draw(window);

    if (m_attacking && m_attackAnimator)
    {
        auto& s = m_attackAnimator->getSprite();
        s.setOrigin({ 0.f, 0.f });
        s.setPosition({ m_position.x - 10.f, m_position.y - 10.f });
        window.draw(s);
    }
    else
    {
        auto& sprite = m_animator.getSprite();
        sprite.setPosition(m_position);
        window.draw(sprite);
    }
}

sf::FloatRect Player::getBounds() const
{
    return sf::FloatRect({ m_position.x + 10.f, m_position.y - 20.f }, { 60.f, 47.f });
}

sf::FloatRect Player::getAttackBounds() const
{
    float offsetX = m_facingRight ? 50.f : -74.f;
    return sf::FloatRect({ m_position.x + offsetX, m_position.y - 10.f }, { 74.f, 76.f });
}