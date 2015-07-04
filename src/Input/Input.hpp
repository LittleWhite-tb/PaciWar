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

#ifndef INPUT_HPP
#define INPUT_HPP

#include <list>
#include <memory>

#include <SFML/System.hpp>

#include "InputDevice.hpp"

class Input
{
    static constexpr float DEADZONE_LIMIT = 0.15f;

private:
    std::list<std::unique_ptr<InputDevice> > m_devices;

    Input(const Input&)=delete;

public:
    /**
     * @brief Input
     * Adds by default the Keyboard and Joystick devices in the manager
     */
    Input();

    /**
     * @brief adds a new InputDevice to the manager
     * We push the new device in front, making it priority
     * @param pNewDevice the new device to take into account
     */
    void add(InputDevice* pNewDevice);

    void update();
    sf::Vector2f getMovement()const;
};

#endif
