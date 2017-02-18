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

#include "Enemy.hpp"

#include <cmath>

#include "GameState.hpp"
#include "Actors/Tracker.hpp"

#include "Collisions/Collider.hpp"
#include "Math/Vector2.hpp"
#include "Math/Interpolation.hpp"

constexpr float Enemy::DEFAULT_SPEED;
constexpr float Enemy::MIN_SPEED;
constexpr float Enemy::BROOD_SPEED_REDUCTION;

const std::string Enemy::m_name = "Enemy";


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

    sf::Transform t;
    t.translate(m_position);

    window.draw(lines,5,sf::LinesStrip,t);
}

void Enemy::getBoundingSpheres(BoundingSpheres &boundingSpheres)const
{
    boundingSpheres.push_back(Sphere(m_position, Enemy::SIZE));
}

void Enemy::update(float ratio)
{
    m_position = Math::Lerp<sf::Vector2f>::get(m_origin,m_destination,ratio);
}

void Enemy::update(GameState& gstate)
{
    m_origin = m_position;
    auto dir = gstate.getObjects().getPlayer()->getPosition() - m_origin;
    Math::normalise(dir);
    m_destination = dir * DEFAULT_SPEED + m_origin;
//    Tracker::update(m_destination,m_rotation,*gstate.getObjects().getPlayer(),m_speed,0.3f,100);
/*
    // Enemies brood behaviour
    // When an enemy is too close, we will check if we need to slow move speed.
    // The slowdown is applied only if the enemy is moving toward another one. It means that
    // if the current one is in the borders of the brood, no slowdown is applied.
    bool canSpeedUp = true;
    auto localEnemies = gstate.getEnemyGrid().getNeighbours(*this);
    for (auto pE : localEnemies)
    {
        if (pE != this) // Avoid colliding with myself
        {
            float newDistance = Math::distance(m_destination,pE->m_destination);
            if ( newDistance < SIZE * SIZE * 15 )
            {
                // We are going toward the enemy
                if ( Math::distance(m_origin,pE->m_destination) > newDistance )
                {
                    canSpeedUp = false;
                    // Slow down
                    m_speed = m_speed * BROOD_SPEED_REDUCTION;
                    m_speed = std::max(m_speed,MIN_SPEED);
                    sf::Vector2f direction = m_destination - m_origin;
                    Math::normalise(direction);
                    m_destination = m_origin + direction * m_speed * static_cast<float>(100);
                    break;
                }
            }
        }
    }

    if (canSpeedUp)
    {
        // Speed up
        m_speed = m_speed / BROOD_SPEED_REDUCTION;
        m_speed = std::min(m_speed,DEFAULT_SPEED);
    }
    */
}
