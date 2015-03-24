#include "Enemy.hpp"

#include <iostream>
#include <cmath>

#include "SFML/Vector2Utils.hpp"
#include "Math/Interpolation.hpp"
#include "Math/constants.hpp"

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

void Enemy::move(unsigned int deltaTime, const Entity &target)
{
    sf::Vector2f targetDir = target.getPosition() - m_position;
    // SFMLUtils::normalise(targetDir);

    float targetRotation = SFMLUtils::getAngle(targetDir);
    m_rotation = Math::EaseInEaseOut<Math::Angle<float> >::get(m_rotation,targetRotation,0.3f);

    sf::Vector2f dir = sf::Vector2f(std::cos(m_rotation*M_PI/180.f),std::sin(m_rotation*M_PI/180.f));

    sf::Vector2f oldPosition = m_position;
    m_position = m_position + dir * (SPEED * deltaTime);
/*
    // Enemies avoidance
    BoundingSpheres self;
    self.push_back(Sphere(m_position, Enemy::SIZE*Enemy::SIZE*2));

    for (auto e : enemies)
    {
        if (e.get() != this) // Avoid colliding with myself
        {
            BoundingSpheres other;
            e->getBoundingSpheres(other);

            if ( Collider::collides(other,self))
            {
                m_position = oldPosition;
                break;
            }
        }
    }
*/
}
