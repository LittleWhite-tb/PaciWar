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

#ifndef __ANGLE_HPP__
#define __ANGLE_HPP__

namespace Math
{
    template <typename T>
    struct Angle
    {
        T value;

        Angle(const T& value):value(value) {}
        operator T()const { return this->value; }

        void wrap()
        {
            while ( this->value > 360 )
            {
                this->value -= 360;
            }
            while ( this->value < -360 )
            {
                this->value += 360;
            }
        }
    };
}

#endif // ANGLE_HPP
