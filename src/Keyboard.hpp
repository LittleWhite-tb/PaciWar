#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <SFML/System.hpp>

#include "Math.hpp"

class Keyboard
{
private:
    static const int LEFT;
    static const int RIGHT;
    static const int UP;
    static const int DOWN;


    sf::Clock m_clock;

    bool m_pressInfo[4];
    sf::Int32 m_pressTimes[4];

    Math::EaseInEaseOut<float> m_pressureInterpolator;

    float getMovementByKey(int key) const;
public:
    Keyboard()
        :m_pressureInterpolator(0,1) {}

    static const int PRESSURE_TIME = 2000;

    void update();

    sf::Vector2f getMovement()const;
};

#endif

