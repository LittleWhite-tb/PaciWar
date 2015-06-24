#include "Player.hpp"

#include "Math/constants.hpp"

#include <limits>

#include "GameState.hpp"

#include "Math/Vector2.hpp"
#include "Math/Interpolation.hpp"

Player::Player()
    :Entity(sf::Vector2f())
{
}
	
void Player::draw(sf::RenderWindow& window) const
{
    const sf::Vertex lines[] =
    {
        sf::Vertex(sf::Vector2f(5, 0)),
        sf::Vertex(sf::Vector2f(-5, 5)),
        sf::Vertex(sf::Vector2f(-5, -5)),
        sf::Vertex(sf::Vector2f(5, 0))
    };

    const sf::Vertex tri2[] =
    {
        sf::Vertex(sf::Vector2f(6, 0)),
        sf::Vertex(sf::Vector2f(-2, 2)),
        sf::Vertex(sf::Vector2f(-2, -2)),
        sf::Vertex(sf::Vector2f(6, 0))
    };

    sf::Transform t;
    t.translate(m_position);
    t.rotate(m_rotation);
	
    window.draw(lines,4,sf::LinesStrip,t);
    window.draw(tri2,4,sf::LinesStrip,t);

    m_engineParticles.draw(window);
}

void Player::debugDraw(sf::RenderWindow& window) const
{
    sf::CircleShape debugCircle(Player::RADIUS);
    debugCircle.setFillColor(sf::Color::Transparent);
    debugCircle.setOutlineThickness(1);
    debugCircle.setOutlineColor(sf::Color(255,0,0));
    debugCircle.setPosition(m_position - sf::Vector2f(Player::RADIUS,Player::RADIUS));

    window.draw(debugCircle);


    debugCircle.setRadius(115);
    debugCircle.setPosition(m_position - sf::Vector2f(115,115));

    window.draw(debugCircle);
}

void Player::update(GameState& gstate)
{
    sf::Vector2f movement = gstate.getInputMovement();
    // Movement here, should be betweend 0 and 1.
    if (movement.x != 0 ||
        movement.y != 0)
    {
        float targetRotation = Math::getAngle(movement);

        // Extra rotation, since the initial ship is drawn up
        m_rotation = Math::EaseInEaseOut<Math::Angle<float> >::get(m_rotation,targetRotation,0.32f);

        sf::Vector2f realDirection = Math::getVectorFromAngle(targetRotation);

        // TODO : Find better way to do it, since we are doing two times the same operations
        sf::Vector2f oldPosition = m_position;
        m_position += realDirection * SPEED * static_cast<float>(gstate.getTime().getElapsedTime());

        gstate.getBorders().clamp(m_position,realDirection,Player::RADIUS);
        m_position = oldPosition + realDirection * SPEED * static_cast<float>(gstate.getTime().getElapsedTime());
    }

    m_engineParticles.update(m_position,-movement,gstate.getTime().getElapsedTime());
}

void Player::getBoundingSpheres(BoundingSpheres &boundingSpheres)const
{
    boundingSpheres.push_back(Sphere(m_position, Player::RADIUS));
}
