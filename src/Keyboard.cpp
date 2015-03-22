#include "Keyboard.hpp"

#include <SFML/Window.hpp>

#include <vector>
#include <iostream>

#include "Math/Interpolation.hpp"

const int Keyboard::LEFT = 0;
const int Keyboard::RIGHT = 1;
const int Keyboard::UP = 2;
const int Keyboard::DOWN = 3;

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
            if ( m_pressInfo[itPair.second] == false ) // If not yet pressed
            {
                // Set time
                m_pressTimes[itPair.second] = m_clock.getElapsedTime().asMilliseconds();
            }
            m_pressInfo[itPair.second] = true;
        }
        else
        {
            m_pressInfo[itPair.second] = false;
        }
    }
}

float Keyboard::getMovementByKey(int key)const
{
    sf::Int32 actualMsTime = m_clock.getElapsedTime().asMilliseconds();
    float keyMovement=0;

    if (m_pressInfo[key])
    {
        sf::Int32 delta = actualMsTime - m_pressTimes[key];
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

    return movement;
}
