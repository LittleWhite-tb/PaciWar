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

#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__

#include <SFML/Graphics.hpp>

#include <vector>

struct Sphere
{
    sf::Vector2f center;
    float radius;

    Sphere(const sf::Vector2f& c, float r):
        center(c),radius(r) {}
    Sphere():
        center(sf::Vector2f(0,0)),radius(0) {}
};

typedef std::vector<Sphere> BoundingSpheres;

#endif
