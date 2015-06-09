#include "Enemy.hpp"

#include <cmath>

#include "GameState.hpp"
#include "Actors/Tracker.hpp"

#include "Collisions/Collider.hpp"
#include "Math/Vector2.hpp"

constexpr float Enemy::DEFAULT_SPEED;
constexpr float Enemy::MIN_SPEED;
constexpr float Enemy::BROOD_SPEED_REDUCTION;


void Enemy::draw(sf::RenderWindow& window)const
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
    Tracker::update(m_position,m_rotation,gstate.getObjects().getPlayer(),m_speed,0.3f,gstate.getTime().getElapsedTime());

    // Enemies brood behaviour
    // When an enemy is too close, we will check if we need to slow move speed.
    // The slowdown is applied only if the enemy is moving toward another one. It means that
    // if the current one is in the borders of the brood, no slowdown is applied.
    auto localEnemies = gstate.getEnemyGrid().getNeighbours(*this);
    for (auto pE : localEnemies)
    {
        if (pE != this) // Avoid colliding with myself
        {
            float newDistance = Math::distance(m_position,pE->getPosition());
            if ( newDistance < SIZE * SIZE * 15 )
            {
                // We are going toward the enemy
                if ( Math::distance(oldPosition,pE->getPosition()) > newDistance )
                {
                    // Slow down
                    m_speed = m_speed * BROOD_SPEED_REDUCTION;
                    m_speed = std::max(m_speed,MIN_SPEED);
                    sf::Vector2f direction = m_position - oldPosition;
                    Math::normalise(direction);
                    m_position = oldPosition + direction * m_speed;
                }
            }
            else
            {
                // Speed up
                m_speed = m_speed / BROOD_SPEED_REDUCTION;
                m_speed = std::min(m_speed,DEFAULT_SPEED);
            }
        }
    }
}
