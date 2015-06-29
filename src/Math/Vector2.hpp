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

#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <SFML/Graphics.hpp>

// TODO Make this class handling all Vector2
namespace Math
{
    float length(const sf::Vector2f& v);
    void normalise(sf::Vector2f& v);
    float distance(const sf::Vector2f& v1, const sf::Vector2f& v2);

    float getAngle(const sf::Vector2f& v);
    sf::Vector2f getVectorFromAngle(float angle); // in degrees
}

#endif
