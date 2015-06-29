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

#include "RadialExplosion.hpp"

void RadialExplosion::draw(sf::RenderWindow& window) const
{
    float outerCircleRadius = m_radius + EFFECT_SIZE/2;
    sf::CircleShape outerCircle(m_radius + EFFECT_SIZE/2);
    outerCircle.setPosition(sf::Vector2f(m_spawnPoint.x - outerCircleRadius, m_spawnPoint.y - outerCircleRadius) );
    outerCircle.setFillColor(sf::Color::Transparent);
    outerCircle.setOutlineColor(sf::Color(220,0,0));
    outerCircle.setOutlineThickness(0.3);

    window.draw(outerCircle);

    sf::CircleShape middleCircle(m_radius);
    middleCircle.setPosition(sf::Vector2f(m_spawnPoint.x - m_radius, m_spawnPoint.y - m_radius));
    middleCircle.setOutlineThickness(0.3);
    middleCircle.setFillColor(sf::Color::Transparent);
    middleCircle.setOutlineColor(sf::Color(220,220,220));

    window.draw(middleCircle);

    float innerCircleRadius = m_radius - EFFECT_SIZE/2;
    if ( innerCircleRadius > 1 )
    {
        sf::CircleShape innerCircle(m_radius - EFFECT_SIZE/2);
        innerCircle.setPosition(sf::Vector2f(m_spawnPoint.x - innerCircleRadius, m_spawnPoint.y - innerCircleRadius));
        innerCircle.setOutlineThickness(0.3);
        innerCircle.setFillColor(sf::Color::Transparent);
        innerCircle.setOutlineColor(sf::Color(220,0,0));

        window.draw(innerCircle);
    }
}

void RadialExplosion::update(unsigned int time)
{
    m_radius+=GROWTH_SPEED*time;
}


bool RadialExplosion::isValid()const
{
    return m_radius > RADIUS_MAX;
}
