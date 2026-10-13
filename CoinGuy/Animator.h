#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

struct Animation
{
    int startY;
    int frameCount;
    float fps;
};

class Animator
{
public:
    Animator(sf::Texture& texture, int frameWidth, int frameHeight);

    void addAnimation(const std::string& name, int startY, int frameCount, float fps);
    void play(const std::string& name);
    void update(float dt);
    void setCustomScale(float s) { m_customScale = s; }
    void setLooping(bool loop) { m_looping = loop; }
    void setFlipped(bool flipped) { m_flipped = flipped; }

    int   getFrameWidth()  const { return m_frameWidth; }
    int   getFrameHeight() const { return m_frameHeight; }
    float getScale()       const { return m_customScale; }
    bool  isFlipped()      const { return m_flipped; }

    sf::Sprite& getSprite();

private:
    sf::Sprite m_sprite;
    int m_frameWidth;
    int m_frameHeight;
    float m_customScale = 2.f;
    bool m_looping = true;
    bool m_flipped = false;

    std::map<std::string, Animation> m_animations;
    std::string m_current;
    int m_currentFrame = 0;
    float m_timer = 0.f;
};