#include "Player.hpp"

Player::Player(const sf::Vector2f& position)
	:m_position(position)
{
}
	
void Player::draw(sf::RenderWindow& window)
{
    const sf::Vertex lines[] =
    {
        sf::Vertex(sf::Vector2f(0, 10)),
        sf::Vertex(sf::Vector2f(5, 0)),
        sf::Vertex(sf::Vector2f(-5, 0)),
        sf::Vertex(sf::Vector2f(0, 10))
    };

    const sf::Vertex tri2[] =
    {
        sf::Vertex(sf::Vector2f(0, 13)),
        sf::Vertex(sf::Vector2f(2, 3)),
        sf::Vertex(sf::Vector2f(-2, 3)),
        sf::Vertex(sf::Vector2f(0, 13))
    };

    sf::Transform t;
    t.translate(m_position);
	
    window.draw(lines,4,sf::LinesStrip,t);
    window.draw(tri2,4,sf::LinesStrip,t);
}

void Player::move(const sf::Vector2f& movement)
{
    m_position += movement;
}
