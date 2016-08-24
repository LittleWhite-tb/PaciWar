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

class Object
{
    static std::map<std::string, unsigned int> m_classCounters;

protected:
    std::string m_id;
    std::string m_classId;

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

    Object(const std::string& id, const std::string& classId)
        :m_id(id),m_classId(classId) {}

};

#endif