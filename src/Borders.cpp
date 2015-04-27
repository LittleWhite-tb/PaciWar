#include "Borders.hpp"

#include "Entity.hpp"

const sf::Color Borders::normalColor = sf::Color(220,220,220);

void Borders::draw(sf::RenderWindow& window)
{
    sf::Color color = normalColor;
    sf::Vertex outerRect[] =
    {
        sf::Vertex(sf::Vector2f(m_limits.left - Borders::GAP, m_limits.top - Borders::GAP),                                   color),
        sf::Vertex(sf::Vector2f(m_limits.left+m_limits.width + Borders::GAP, m_limits.top - Borders::GAP),                    color),
        sf::Vertex(sf::Vector2f(m_limits.left+m_limits.width + Borders::GAP, m_limits.top+m_limits.height + Borders::GAP),    color),
        sf::Vertex(sf::Vector2f(m_limits.left - Borders::GAP, m_limits.top+m_limits.height + Borders::GAP),                   color),
        sf::Vertex(sf::Vector2f(m_limits.left - Borders::GAP, m_limits.top - Borders::GAP),                                   color)
    };

    // Second lines
    sf::Vertex innerRect[] =
    {
        sf::Vertex(sf::Vector2f(m_limits.left + Borders::GAP, m_limits.top + Borders::GAP),                                   color),
        sf::Vertex(sf::Vector2f(m_limits.left+m_limits.width - Borders::GAP, m_limits.top + Borders::GAP),                    color),
        sf::Vertex(sf::Vector2f(m_limits.left+m_limits.width - Borders::GAP, m_limits.top+m_limits.height - Borders::GAP),    color),
        sf::Vertex(sf::Vector2f(m_limits.left + Borders::GAP, m_limits.top+m_limits.height - Borders::GAP),                   color),
        sf::Vertex(sf::Vector2f(m_limits.left + Borders::GAP, m_limits.top + Borders::GAP),                                   color)
    };

    window.draw(outerRect,5,sf::LinesStrip);
    window.draw(innerRect,5,sf::LinesStrip);
}

bool Borders::isOutside(const Entity& entity)
{

}
