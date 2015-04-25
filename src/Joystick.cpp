#include "Joystick.hpp"

#include <iostream>
#include <cassert>

#include <SFML/Window.hpp>

#include "SFML/Vector2Utils.hpp"


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
            return sf::Vector2f(sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::X)/100.f,
                                sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::Y)/100.f);
        }
    }
    else
    {
        assert(false);
        return sf::Vector2f(0,0);
    }
}
