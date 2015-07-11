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

#include "Bonus.hpp"

#include <cmath>

#include "Math/Vector2.hpp"
#include "Actors/Tracker.hpp"

#include "GameState.hpp"

#include <Collisions/Collider.hpp>

const sf::Color Bonus::normalColor = sf::Color(120,230,50);
const sf::Color Bonus::lightColor = sf::Color(250,250,170);

Bonus::Bonus(const sf::Vector2f& position)
    :Entity(position),m_color(normalColor),m_life(LIFETIME),
     m_momentum(0.02f,0.2f)
{
}

void Bonus::draw(sf::RenderWindow& window) const
{
    static constexpr float shapeSize = 3;

    sf::Vertex lines[] =
    {
        sf::Vertex(sf::Vector2f(0         , shapeSize ), m_color),
        sf::Vertex(sf::Vector2f(shapeSize , 0         ), m_color),
        sf::Vertex(sf::Vector2f(0         , -shapeSize), m_color),
        sf::Vertex(sf::Vector2f(-shapeSize, 0         ), m_color),
        sf::Vertex(sf::Vector2f(0         , shapeSize ), m_color)
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

void Bonus::update(GameState& gstate)
{
    m_momentum.update(this->m_position,this->m_rotation,gstate.getTime().getElapsedTime());

    const Player& target = gstate.getObjects().getPlayer();
    float targetDistance = Math::distance(target.getPosition(),this->getPosition());
    if ( targetDistance < MAGNET_DISTANCE*MAGNET_DISTANCE )
    {
        Tracker::update(m_position,m_rotation,target,SPEED,0.5f,gstate.getTime().getElapsedTime());

        // Normally, we can't lose bonus/untract player
        m_life = LIFETIME;
    }

    m_life -= gstate.getTime().getElapsedTime();
    if (m_life < BLINK_TIME)
    {
        if ((m_life / BLINK_DELAY) % 2)
        {
            m_color = normalColor;
        }
        else
        {
            m_color = lightColor;
        }
    }
}
