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

#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP

#include <random>
#include <functional>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class RandomGenerator
{
private:
    static std::mt19937 m_generator;

public:

    static float getFloat(float min, float max);
    static int getInt(int min, int max);

    static sf::Vector2i getIntVector(int minx, int maxx, int miny, int maxy);
    static sf::Vector2f getFloatVector(float minx, float maxx, float miny, float maxy);

    /**
     * @brief Gets a random normalized direction
     * @return the random normalized direction
     */
    static sf::Vector2f getNormalizedDirection();

    /**
     * @brief Gets a random colour
     * @param min
     * @param max
     * @return the random colour
     */
    static sf::Color getColor(unsigned char min, unsigned char max);
};

#endif
