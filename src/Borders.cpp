#include "Borders.hpp"

#include <algorithm>

#include "Entity.hpp"
#include "Math/ColorInterpolation.hpp"

const sf::Color Borders::normalColor = sf::Color(220,220,220);

Borders::Location Borders::getCollisionLocation(const sf::Vector2f& position)const
{
    Borders::Location location = 0;

    if ( position.x <= m_innerLimits.left )
    {
        location |= Borders::LEFT;
    }

    if ( position.x >= m_innerLimits.left+m_innerLimits.width)
    {
        location |= Borders::RIGHT;
    }

    if ( position.y <= m_innerLimits.top )
    {
        location |= Borders::TOP;
    }

    if ( position.y >= m_innerLimits.top+m_innerLimits.height )
    {
        location |= Borders::DOWN;
    }

    return location;
}

void Borders::draw(sf::RenderWindow& window)
{
    sf::Color color;
    if ( m_impulseCounter == 0 )
    {
        color = normalColor;
    }
    else
    {
        color = Math::Lerp<sf::Color>::get(normalColor,m_impulseColor,m_impulseCounter/static_cast<float>(IMPULSE_TIME));
    }

    sf::Vertex outerRect[] =
    {
        sf::Vertex(sf::Vector2f(m_outerLimits.left,                     m_outerLimits.top),                      color),
        sf::Vertex(sf::Vector2f(m_outerLimits.left+m_outerLimits.width, m_outerLimits.top),                      color),
        sf::Vertex(sf::Vector2f(m_outerLimits.left+m_outerLimits.width, m_outerLimits.top+m_outerLimits.height), color),
        sf::Vertex(sf::Vector2f(m_outerLimits.left,                     m_outerLimits.top+m_outerLimits.height), color),
        sf::Vertex(sf::Vector2f(m_outerLimits.left,                     m_outerLimits.top),                      color)
    };

    // Second lines
    sf::Vertex innerRect[] =
    {
        sf::Vertex(sf::Vector2f(m_innerLimits.left,                     m_innerLimits.top),                      color),
        sf::Vertex(sf::Vector2f(m_innerLimits.left+m_innerLimits.width, m_innerLimits.top),                      color),
        sf::Vertex(sf::Vector2f(m_innerLimits.left+m_innerLimits.width, m_innerLimits.top+m_innerLimits.height), color),
        sf::Vertex(sf::Vector2f(m_innerLimits.left,                     m_innerLimits.top+m_innerLimits.height), color),
        sf::Vertex(sf::Vector2f(m_innerLimits.left,                     m_innerLimits.top),                      color)
    };

    window.draw(outerRect,5,sf::LinesStrip);
    window.draw(innerRect,5,sf::LinesStrip);
}

void Borders::update(unsigned int deltaTime)
{
    m_impulseCounter = std::max(m_impulseCounter-static_cast<int>(deltaTime),0);
}

bool Borders::isOutside(const sf::Vector2f& position)
{
    return ! m_innerLimits.contains(sf::Vector2i(position));
}


bool Borders::isOutside(const Entity& entity)
{
    return isOutside(entity.getPosition());
}

void Borders::clamp(const sf::Vector2f& position, sf::Vector2f& direction) const
{
    Borders::Location location = getCollisionLocation(position);

    if ( location & Borders::LEFT )
        if ( direction.x < 0)
            direction.x = 0;

    if ( location & Borders::RIGHT )
        if ( direction.x > 0 )
            direction.x = 0;

    if ( location & Borders::TOP )
        if ( direction.y < 0 )
             direction.y = 0;

    if ( location & Borders::DOWN )
        if ( direction.y > 0 )
            direction.y = 0;
}

void Borders::bounce(const sf::Vector2f& position, sf::Vector2f& direction)const
{
    Borders::Location location = getCollisionLocation(position);

    if ( location & Borders::LEFT ||
         location & Borders::RIGHT )
            direction.x = -direction.x;

    if ( location & Borders::TOP ||
         location & Borders::DOWN )
            direction.y = -direction.y;
}

void Borders::impulse(const sf::Color& impulseColor)
{
    m_impulseColor = impulseColor;
    m_impulseCounter = Borders::IMPULSE_TIME;
}
