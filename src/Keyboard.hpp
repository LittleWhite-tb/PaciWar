#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <SFML/System.hpp>

#include "Math/Interpolation.hpp"

class Keyboard
{
private:
    static constexpr int LEFT = 0;
    static constexpr int RIGHT = 1;
    static constexpr int UP = 2;
    static constexpr int DOWN = 3;

    static const int PRESSURE_TIME = 200;

    sf::Clock m_clock;

    // Contains boolean to remember if the key is pressed, and time of the pressure
    std::pair<bool, sf::Int32> m_pressInfos[4];

    Math::EaseInEaseOut<float> m_pressureInterpolator;

    float getMovementByKey(int key) const;
public:
    Keyboard()
        :m_pressureInterpolator(0,1) {}

    void update();

    sf::Vector2f getMovement()const;
};

#endif

