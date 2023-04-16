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

#include "Joystick.hpp"

#include <iostream>
#include <cassert>

#include <SFML/Window.hpp>

#include "Math/Vector2.hpp"


void Joystick::update()
{
    if (sf::Joystick::isConnected(0))
    {
        if ( m_isEnabled == false ) // Was not connected until now
        {
            std::cout << "Joystick has been plugged" << std::endl;
#ifndef NDEBUG
            std::cout << "===> " << sf::Joystick::getIdentification(0).name.toAnsiString() << std::endl;
#endif
            if ( sf::Joystick::hasAxis(0,sf::Joystick::Axis::X) == false || sf::Joystick::hasAxis(0,sf::Joystick::Axis::Y) == false )
            {
                std::cout << "Joystick invalid" << std::endl;
            }
            m_isEnabled=true;
        }
    }
    else
    {
        if ( m_isEnabled == true )
        {
            std::cout << "Joystick disconnected" << std::endl;
            m_isEnabled = false;
        }
    }
}

sf::Vector2f Joystick::getMovement()const
{
    if ( m_isEnabled )
    {
        if ( sf::Joystick::hasAxis(0,sf::Joystick::Axis::X) && sf::Joystick::hasAxis(0,sf::Joystick::Axis::Y) )
        {
            sf::Vector2f movement = sf::Vector2f(sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::X)/100.f,
                                                 sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::Y)/100.f);
            Math::normalise(movement);
            return movement;
        }
    }
    else
    {
        assert(false);
    }
    return sf::Vector2f(0,0);
}
