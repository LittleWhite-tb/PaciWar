/*
 * PaciWar : Remake of the "pacifism" mode from Geometry Wars 2
 * Copyright (C) 2014-2016 LittleWhite (lw.demoscene@gmail.com)
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
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <map>
#include <string>

/**
 * Offers a template way to give a static name to a class
 */
template <class T>
class Named {
public:
    /**
     * @brief getName returns the name of the class passed as template argument
     * @return
     */
    static const std::string& getName() { return T::m_name; }
};

/**
 * @brief Base class for Entity Component System
 * Inherit this class in all object of the game.
 * The ID is auto increment ID to record count of this kind of Object.
 * @todo Replace this class by a class only containing a list of component
 */
class Object
{
    static std::map<std::string, unsigned int> m_classCounters; //! Keeps track of number of instances
    // std::vector<Component> m_components; //! The list of component

protected:
    std::string m_classId; //! Name of this object
    std::string m_id;   //! ID of this kind of object

public:
    Object(const std::string& classId)
        :m_classId(classId) {
        auto item = m_classCounters.find(classId);
        if (item != std::end(m_classCounters)) {
            item->second++;
        }
        else {
            m_classCounters[classId] = 1;
        }
        m_id = std::to_string(m_classCounters[classId]);
    }

    /*
     * Actually, there is no need to directly pass the ID
    Object(const std::string& classId, const std::string& id)
        :m_classId(classId),m_id(id) {}
    */

    const std::string& getId()const { return m_id; }
    const std::string& getClassId()const { return m_classId; }

};

#endif
