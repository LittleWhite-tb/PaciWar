#include "Barrier.hpp"

Barrier::Barrier(const sf::Vector2f& position)
	:m_position(position)
{
}
	
void Barrier::draw(sf::RenderWindow& window)
{
    const int barrierSize = 24;
    const sf::Vertex lines[] =
	{
        sf::Vertex(sf::Vector2f(-barrierSize/2, 0)),
        sf::Vertex(sf::Vector2f(0, -barrierSize/3)),
        sf::Vertex(sf::Vector2f(0, barrierSize/3)),
        sf::Vertex(sf::Vector2f(-barrierSize/2, 0)),
        sf::Vertex(sf::Vector2f(barrierSize/2 + barrierSize*3, 0)),
        sf::Vertex(sf::Vector2f(barrierSize*3, -barrierSize/3)),
        sf::Vertex(sf::Vector2f(barrierSize*3, barrierSize/3)),
        sf::Vertex(sf::Vector2f(barrierSize/2 + barrierSize*3, 0))
	};

    sf::Transform t;
    t.translate(m_position);

    window.draw(lines,8 ,sf::LinesStrip,t);
}
