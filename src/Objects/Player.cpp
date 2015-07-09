/*
 * PaciWar : Remake of the "pacifism" mode from Geometry Wars 2
 * Copyright (C) 2014-2015 LittleWhite (lw.demoscene@gmail.com)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Player.hpp"

#include "Math/constants.hpp"

#include <limits>

#include "GameState.hpp"

#include "Math/Vector2.hpp"
#include "Math/Interpolation.hpp"

#include <iostream>

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
}

void Player::update(GameState& gstate)
{
    sf::Vector2f movement = gstate.getInputMovement();
    std::cout << "Root movement : " << movement.x << ";" << movement.y << std::endl;
    // Movement here, should be betweend 0 and 1.
    if (movement.x != 0 ||
        movement.y != 0)
    {
        float targetRotation = Math::getAngle(movement);

        // Extra rotation, since the initial ship is drawn up
        m_rotation = Math::EaseInEaseOut<Math::Angle<float> >::get(m_rotation,targetRotation,0.32f);
        std::cout << "TargetRot : " << targetRotation << " rot : " << m_rotation << std::endl;
        sf::Vector2f realDirection = Math::getVectorFromAngle(targetRotation);

        // TODO : Find better way to do it, since we are doing two times the same operations
        sf::Vector2f oldPosition = m_position;
        m_position += realDirection * SPEED * static_cast<float>(gstate.getTime().getElapsedTime());
        std::cout << "RealDir : " << realDirection.x << ";" << realDirection.y << " Delta : " << static_cast<float>(gstate.getTime().getElapsedTime()) << std::endl;

        gstate.getBorders().clamp(m_position,realDirection,Player::RADIUS);
        m_position = oldPosition + realDirection * SPEED * static_cast<float>(gstate.getTime().getElapsedTime());
    }
    std::cout << "Movement : " << movement.x << ";" << movement.y << std::endl;
    std::cout << "Position : " << m_position.x << ";" << m_position.y << " Rotation : " << m_rotation << std::endl;
    std::cout << "---" << std::endl;

    m_engineParticles.update(m_position,-movement,gstate.getTime().getElapsedTime());
}

void Player::getBoundingSpheres(BoundingSpheres &boundingSpheres)const
{
    boundingSpheres.push_back(Sphere(m_position, Player::RADIUS));
}
