#include "Player.hpp"

#include "Math/constants.hpp"

#include <limits>

#include "SFML/Vector2Utils.hpp"
#include "Math/Interpolation.hpp"

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

void Player::move(const sf::Vector2f& movement, float time)
{
    // Movement here, should be betweend 0 and 1.
    m_position += movement * SPEED * time;
    if (movement.x != 0 ||
        movement.y != 0)
    {
        float targetRotation = SFMLUtils::getAngle(movement);

        // Extra rotation, since the initial ship is drawn up
        targetRotation+=90;
        m_rotation = Math::EaseInEaseOut<Math::Angle<float> >::get(m_rotation,targetRotation,0.3f);
    }
}

void Player::getBoundingSpheres(BoundingSpheres &boundingSpheres)const
{
    boundingSpheres.push_back(Sphere(m_position, Player::radius));
}
