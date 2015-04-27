#ifndef BORDERS_HPP
#define BORDERS_HPP

#include <SFML/Graphics.hpp>

class Entity;

class Borders
{
    static constexpr float GAP = 1.5f;

    static const sf::Color normalColor;

private:
    sf::IntRect m_limits;
    int m_onImpulse;

public:
    Borders(const sf::IntRect& limits)
        :m_limits(limits),m_onImpulse(0) {}

    void draw(sf::RenderWindow& window);

    bool isOutside(const Entity& entity);
};

#endif
