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
    unsigned int m_seed;
    std::mt19937 m_generator;

public:
    unsigned int m_counter;

    RandomGenerator();

    float getFloat(float min, float max);
    int getInt(int min, int max);

    sf::Vector2i getIntVector(int minx, int maxx, int miny, int maxy);
    sf::Vector2f getFloatVector(float minx, float maxx, float miny, float maxy);

    /**
     * @brief Gets a random normalized direction
     * @return the random normalized direction
     */
    sf::Vector2f getNormalizedDirection();

    /**
     * @brief Gets a random colour
     * @param min
     * @param max
     * @return the random colour
     */
    sf::Color getColor(unsigned char min, unsigned char max);

    unsigned int getSeed();
    void setSeed(unsigned int newSeed);
};

/**
 * @brief \a RndGenerators offers two generators. The \a basic_gen can
 * be used when you need numbers and does not care about having the same
 * between each game. \a det_gen should be used when the numbers should be
 * the same between games.
 * To allow the repetitivity, you have to assure that you are always calling
 * the same amount of time the generator. Thus, particles should use \a basic_gen
 * and enemies spawning use \a det_gen.
 * Finaly, this also means that to enable repetitivity, you must set the seed (\a RandomGenerator::setSeed())
 * for \a det_gen.
 */
class RndGenerators
{
public:
    /**
     * @brief Basic random generator (when repetitivity is not essential)
     */
    static RandomGenerator basic_gen;
    /**
     * @brief Deterministic generator
     */
    static RandomGenerator det_gen;
};

#endif
