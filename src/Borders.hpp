#ifndef BORDERS_HPP
#define BORDERS_HPP

#include <SFML/Graphics.hpp>

class Entity;

class Borders
{
    static constexpr float GAP = 1.5f;

    static const sf::Color normalColor;

    typedef unsigned int Location;
    static constexpr Location LEFT = 1;
    static constexpr Location TOP = 2;
    static constexpr Location RIGHT = 4;
    static constexpr Location DOWN = 8;

private:
    sf::IntRect m_limits;
    sf::IntRect m_innerLimits;
    int m_onImpulse;

    Location getCollisionLocation(const sf::Vector2f& position)const;

public:
    Borders(const sf::IntRect& limits)
        :m_limits(limits),m_innerLimits(m_limits.left+GAP,
                                        m_limits.top+GAP,
                                        m_limits.width-GAP,
                                        m_limits.height-GAP),
         m_onImpulse(0) {}

    void draw(sf::RenderWindow& window);

    bool isOutside(const sf::Vector2f& position);
    bool isOutside(const Entity& entity);

    void clamp(const sf::Vector2f& position, sf::Vector2f& direction)const;
    void bounce(const sf::Vector2f& position, sf::Vector2f& direction)const;

    sf::IntRect getLimits()const { return m_limits; }
};

#endif