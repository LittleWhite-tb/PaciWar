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

#include "Keyboard.hpp"

#include <SFML/Window.hpp>

#include <vector>
#include <iostream>

#include "Math/Interpolation.hpp"
#include "Math/Vector2.hpp"

constexpr int Keyboard::LEFT;
constexpr int Keyboard::RIGHT;
constexpr int Keyboard::UP;
constexpr int Keyboard::DOWN;

void Keyboard::update()
{
    static const std::vector<std::pair< sf::Keyboard::Key , int > > m_keyMatch =
    {
        {sf::Keyboard::Left, Keyboard::LEFT },
        {sf::Keyboard::Right, Keyboard::RIGHT },
        {sf::Keyboard::Up, Keyboard::UP },
        {sf::Keyboard::Down, Keyboard::DOWN }
    };

    for(auto itPair : m_keyMatch)
    {
        if ( sf::Keyboard::isKeyPressed(itPair.first))
        {
            if ( m_pressInfos[itPair.second].first == false ) // If not yet pressed
            {
                // Set time
                m_pressInfos[itPair.second].second = m_clock.getElapsedTime().asMilliseconds();
            }
            m_pressInfos[itPair.second].first = true;
        }
        else
        {
            m_pressInfos[itPair.second].first = false;
        }
    }
}

float Keyboard::getMovementByKey(int key)const
{
    sf::Int32 actualMsTime = m_clock.getElapsedTime().asMilliseconds();
    float keyMovement=0;

    if (m_pressInfos[key].first)
    {
        sf::Int32 delta = actualMsTime - m_pressInfos[key].second;
        if ( delta > PRESSURE_TIME )
        {
            keyMovement = 1.0f;
        }
        else
        {
            keyMovement = m_pressureInterpolator.get(delta/(float)PRESSURE_TIME);
        }
    }

    return keyMovement;
}

sf::Vector2f Keyboard::getMovement()const
{
    sf::Vector2f movement;

    movement.x -= getMovementByKey(Keyboard::LEFT);
    movement.x += getMovementByKey(Keyboard::RIGHT);
    movement.y -= getMovementByKey(Keyboard::UP);
    movement.y += getMovementByKey(Keyboard::DOWN);

    Math::normalise(movement);
    return movement;
}
