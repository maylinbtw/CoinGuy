#include "Animator.h"

Animator::Animator(sf::Texture& texture, int frameWidth, int frameHeight)
    : m_sprite(texture)
    , m_frameWidth(frameWidth)
    , m_frameHeight(frameHeight)
{}

void Animator::addAnimation(const std::string& name, int startY, int frameCount, float fps)
{
    m_animations[name] = { startY, frameCount, fps };
}

void Animator::play(const std::string& name)
{
    if (m_current == name) return;
    m_current = name;
    m_currentFrame = 0;
    m_timer = 0.f;
    m_looping = true;
    auto& anim = m_animations[m_current];
    m_sprite.setTextureRect(sf::IntRect({ 0, anim.startY }, { m_frameWidth, m_frameHeight }));
}

void Animator::update(float dt)
{
    if (m_current.empty()) return;
    auto& anim = m_animations[m_current];

    m_timer += dt;
    if (m_timer >= 1.f / anim.fps)
    {
        m_timer = 0.f;
        if (m_looping)
            m_currentFrame = (m_currentFrame + 1) % anim.frameCount;
        else
            m_currentFrame = std::min(m_currentFrame + 1, anim.frameCount - 1);
    }

    int x = m_currentFrame * m_frameWidth;
    int y = anim.startY;

    if (m_flipped)
        m_sprite.setTextureRect(sf::IntRect({ x + m_frameWidth, y }, { -m_frameWidth, m_frameHeight }));
    else
        m_sprite.setTextureRect(sf::IntRect({ x, y }, { m_frameWidth, m_frameHeight }));

    m_sprite.setOrigin({ 0.f, 0.f });
    m_sprite.setScale({ m_customScale, m_customScale });
}

sf::Sprite& Animator::getSprite()
{
    return m_sprite;
}