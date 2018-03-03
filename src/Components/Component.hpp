/*
 * PaciWar : Remake of the "pacifism" mode from Geometry Wars 2
 * Copyright (C) 2014-2017 LittleWhite (lw.demoscene@gmail.com)
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>

/**
 * @brief Base class for Entity Component System
 * This class does only have a name and should be inherited by each class implementing behavior in Object
 */
class Component
{
private:
    std::string m_name;

protected:
    Component(const std::string& name)
        :m_name(name) {}

public:
    virtual ~Component() {}

    const std::string& getName()const { return m_name; }
};

#endif
