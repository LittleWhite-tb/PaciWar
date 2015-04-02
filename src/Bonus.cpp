#include "Bonus.hpp"

#include <cmath>

#include "SFML/Vector2Utils.hpp"
#include "Tracker.hpp"

#include <Collisions/Collider.hpp>

void Bonus::draw(sf::RenderWindow& window)
{
    static constexpr float shapeSize = 3;
    sf::Vertex lines[] =
    {
        sf::Vertex(sf::Vector2f(0         , shapeSize )),
        sf::Vertex(sf::Vector2f(shapeSize , 0         )),
        sf::Vertex(sf::Vector2f(0         , -shapeSize)),
        sf::Vertex(sf::Vector2f(-shapeSize, 0         )),
        sf::Vertex(sf::Vector2f(0         , shapeSize ))
    };


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

void Bonus::getBoundingSpheres(BoundingSpheres &boundingSpheres)const
{
    boundingSpheres.push_back(Sphere(m_position, Bonus::SIZE));
}

void Bonus::move(unsigned int deltaTime, const Entity &target)
{
    m_momentum.update(this->m_position,this->m_rotation,deltaTime);

    float targetDistance = SFMLUtils::distance(target.getPosition(),this->getPosition());
    if ( targetDistance < MAGNET_DISTANCE*MAGNET_DISTANCE )
    {
        Tracker::update(m_position,m_rotation,target,SPEED,0.5f,deltaTime);

        // Normally, we can't lose bonus/untract player
        m_life = 1000;
    }
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
    m_life -= deltaTime;
}
