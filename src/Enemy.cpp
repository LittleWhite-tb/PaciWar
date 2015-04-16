#include "Enemy.hpp"

#include <cmath>

#include "GameState.hpp"
#include "Tracker.hpp"

#include <Collisions/Collider.hpp>


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

void Enemy::getBoundingSpheres(BoundingSpheres &boundingSpheres)const
{
    boundingSpheres.push_back(Sphere(m_position, Enemy::SIZE));
}

void Enemy::update(GameState& gstate)
{
    sf::Vector2f oldPosition = m_position;
    Tracker::update(m_position,m_rotation,gstate.getObjects().getPlayer(),SPEED,0.3f,gstate.getTime().getElapsedTime());

    // Enemies avoidance
    BoundingSpheres self;
    self.push_back(Sphere(m_position, Enemy::SIZE*Enemy::SIZE*2));

    Pool<Enemy>::const_iterator itBarrier = gstate.getObjects().getEnemies().cbegin();
    for ( ; itBarrier != gstate.getObjects().getEnemies().cend() ; ++itBarrier)
    {
        if (itBarrier->getPosition() != oldPosition) // Avoid colliding with myself
                                                     // HACK Not good at all
        {
            BoundingSpheres other;
            itBarrier->getBoundingSpheres(other);

            if ( Collider::collides(other,self))
            {
                m_position = oldPosition;
                break;
            }
        }
    }
}
