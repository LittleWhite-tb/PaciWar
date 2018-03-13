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
#include <iostream>

#include "GameState.hpp"
#include "Actors/Tracker.hpp"

#include "Collisions/Collider.hpp"
#include "Math/Vector2.hpp"
#include "Math/Interpolation.hpp"

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

void Enemy::update(GameState &gstate)
{

}

void Enemy::update(GameState &gstate, const sf::Vector2f& centroid, const sf::Vector2f& velocity)
{
    m_origin = m_position;
    auto dir = gstate.getObjects().getPlayer().getPosition() - m_origin;
    Math::normalise(dir);

    sf::Vector2f v2;
    auto enemies = gstate.getEnemyGrid().getNeighbours(*this);
    for (auto pE : enemies)
    {
        if (pE != this) // Avoid colliding with myself
        {
            auto dirToOther = pE->getPosition() - this->getPosition();
            v2 = v2 - dirToOther;
        }
    }

    sf::Vector2f v1 = (centroid - this->getPosition()) / (float)(gstate.nbEnemies()-1);
    v1 = v1 - this->getPosition();
    sf::Vector2f v3 = (velocity - this->getVelocity()) / 2.f;
    Math::normalise(v1); // or 1%
    Math::normalise(v2);
    Math::normalise(v3); // or 12%

    if(gstate.nbEnemies() == 1)
    {
        m_velocity = dir;
    }
    else
    {
        m_velocity = v1 + v2 + v3 + dir;
    }
    Math::normalise(m_velocity);

    m_position = m_position + m_velocity * DEFAULT_SPEED;
}

