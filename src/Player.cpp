#include "Player.hpp"

#include <cmath>
#include <limits>

#include "Math/Interpolation.hpp"

const float Player::SPEED=10.0f;
const float Player::radius=6.0f;

Player::Player(const sf::Vector2f& position)
    :Entity(position)
{
}
	
void Player::draw(sf::RenderWindow& window)
{
    const sf::Vertex lines[] =
    {
        sf::Vertex(sf::Vector2f(0, -5)),
        sf::Vertex(sf::Vector2f(5, 5)),
        sf::Vertex(sf::Vector2f(-5, 5)),
        sf::Vertex(sf::Vector2f(0, -5))
    };

    const sf::Vertex tri2[] =
    {
        sf::Vertex(sf::Vector2f(0, -6)),
        sf::Vertex(sf::Vector2f(2, 2)),
        sf::Vertex(sf::Vector2f(-2, 2)),
        sf::Vertex(sf::Vector2f(0, -6))
    };

    sf::Transform t;
    t.translate(m_position);
    t.rotate(m_rotation);
	
    window.draw(lines,4,sf::LinesStrip,t);
    window.draw(tri2,4,sf::LinesStrip,t);
}

void Player::debugDraw(sf::RenderWindow& window)
{
    sf::CircleShape debugCircle(Player::radius);
    debugCircle.setFillColor(sf::Color::Transparent);
    debugCircle.setOutlineThickness(1);
    debugCircle.setOutlineColor(sf::Color(255,0,0));
    debugCircle.setPosition(m_position - sf::Vector2f(Player::radius,Player::radius));

    window.draw(debugCircle);
}

void Player::move(const sf::Vector2f& movement)
{
    // Movement here, should be betweend 0 and 1.
    m_position += movement * SPEED;
    if (movement.x != 0 ||
        movement.y != 0)
    {
        float targetRotation = atan(movement.y/movement.x) * 180.f/M_PI;
        if ( movement.x >= 0 ) // First quadrant, is ok
        {
            if ( movement.y < 0 ) // Forth quadran
            {
                targetRotation += 360;
            }
        }
        if ( (movement.x < 0) ) // Second and third
        {
            targetRotation += 180;
        }

        // Extra rotation, since the initial ship is drawn up
        targetRotation+=90;
        m_rotation = Math::EaseInEaseOut<Math::Angle<float> >::get(m_rotation,targetRotation,0.2f);
    }
}

void Player::getBoundingSpheres(BoundingSpheres &boundingSpheres)const
{
    boundingSpheres.push_back(Sphere(m_position, Player::radius));
}
