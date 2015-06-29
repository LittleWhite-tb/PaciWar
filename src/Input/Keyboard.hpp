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

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "InputDevice.hpp"

#include "Math/Interpolation.hpp"

class Keyboard : public InputDevice
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

