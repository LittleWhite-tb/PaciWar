#include "Enemy.hpp"

void Enemy::draw(sf::RenderWindow& window)
{

	sf::Vertex lines[] =
	{
        sf::Vertex(sf::Vector2f(0, 10)),
        sf::Vertex(sf::Vector2f(10, 0)),
        sf::Vertex(sf::Vector2f(0, -10)),
        sf::Vertex(sf::Vector2f(-10, 0)),
        sf::Vertex(sf::Vector2f( 0, 10))
	};
	/*
	sf::RectangleShape lines[] = 
	{
		sf::RectangleShape(sf::Vector2f(m_position.x + 0, m_position.y + 10)),
		sf::RectangleShape(sf::Vector2f(m_position.x + 10, m_position.y + 0)),
		sf::RectangleShape(sf::Vector2f(m_position.x + 0, m_position.y - 10)),
		sf::RectangleShape(sf::Vector2f(m_position.x - 10, m_position.y + 0)),
		sf::RectangleShape(sf::Vector2f(m_position.x + 10, m_position.y + 10))
	};
	*/

    sf::Transform t;
    t.translate(m_position);

    window.draw(lines,5,sf::LinesStrip,t);
/*
    const unsigned int size=10;J
	sf::RectangleShape line(sf::Vector2f(size, 2));
	line.setOutlineThickness(1);
	line.rotate(45);
	line.setPosition(m_position.x,m_position.y-size);
	window.draw(line);
	line.rotate(90);
	line.setPosition(m_position.x+size,m_position.y);
	window.draw(line);
	line.rotate(90);
	line.setPosition(m_position.x,m_position.y+size);
	window.draw(line);
	line.rotate(90);
	line.setPosition(m_position.x-size,m_position.y);
	window.draw(line);
*/
}

Sphere Enemy::getBoundingSphere()const
{
    return Sphere(m_position, 2);
}
