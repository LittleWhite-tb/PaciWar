#include "Keyboard.hpp"

#include <SFML/Window.hpp>

#include <vector>
#include <iostream>

#include "Math/Interpolation.hpp"
#include "SFML/Vector2Utils.hpp"

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

    return movement;
}
