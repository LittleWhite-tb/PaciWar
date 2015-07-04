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

#include "Input.hpp"

#include <cassert>

#include "InputDevice.hpp"
#include "Joystick.hpp"
#include "Keyboard.hpp"
#include "Replayer.hpp"

#include "Math/Vector2.hpp"

#include "Settings.hpp"

Input::Input()
{
#if TRACE_MODE == 1
    m_devices.push_back(std::unique_ptr<InputDevice>(new Replayer(Settings::inputFile)));
#endif
    // Order is important since only first usable will be counted
    m_devices.push_back(std::unique_ptr<InputDevice>(new Joystick()));
    m_devices.push_back(std::unique_ptr<InputDevice>(new Keyboard()));
}

void Input::update()
{
    for(auto& device : m_devices)
    {
        device->update();
    }
}

sf::Vector2f Input::getMovement()const
{
    for(const auto& device : m_devices)
    {
        if (device->enabled())
        {
            sf::Vector2f movement = device->getMovement();
            // A device can return 0,0 for several reason. So, we continue to check
            // the devices in case that the user uses another device actively
            if (Math::length(movement) >= DEADZONE_LIMIT)
            {
                Math::normalise(movement);
                return movement;
            }
        }
    }
    return sf::Vector2f(0,0);
}
