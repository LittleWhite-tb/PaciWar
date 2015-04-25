#include "Joystick.hpp"

#include <SFML/Window.hpp>

#include <iostream>
#include <cassert>



void Joystick::update()
{
    if (sf::Joystick::isConnected(0))
    {
        if ( m_isConnected == false ) // Was not connected until now
        {
            std::cout << "Joystick has been plugged" << std::endl;
#ifndef NDEBUG
            std::cout << "===> " << sf::Joystick::getIdentification(0).name << std::endl;
#endif
            if ( sf::Joystick::hasAxis(0,sf::Joystick::Axis::X) == false || sf::Joystick::hasAxis(0,sf::Joystick::Axis::Y) == false )
            {
                std::cout << "Joystick invalid" << std::endl;
            }
        }
        m_isConnected=false;
    }
}

sf::Vector2f Joystick::getMovement()const
{
    if ( m_isConnected )
    {
        if ( sf::Joystick::hasAxis(0,sf::Joystick::Axis::X) && sf::Joystick::hasAxis(0,sf::Joystick::Axis::Y) )
        {
            return sf::Vector2f(
                        sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::X),
                        sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::Y));
        }
    }
    else
    {
        assert(false);
        return sf::Vector2f(0,0);
    }
}
