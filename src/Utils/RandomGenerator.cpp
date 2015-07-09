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

#include "RandomGenerator.hpp"

#include "Math/Vector2.hpp"

#include <iostream>

RandomGenerator RndGenerators::basic_gen = RandomGenerator();
RandomGenerator RndGenerators::det_gen = RandomGenerator();


RandomGenerator::RandomGenerator()
    :m_seed(std::random_device()()),m_generator(std::mt19937(m_seed)),m_counter(0)
{
    std::cout << "Gen with seed : " << m_seed << std::endl;
}

float RandomGenerator::getFloat(float min, float max)
{
    m_counter++;
    std::uniform_real_distribution<> dist(min,max);
    return dist(m_generator);
}

int RandomGenerator::getInt(int min, int max)
{
    m_counter++;
    std::uniform_int_distribution<> dist(min,max);
    return dist(m_generator);
}

sf::Vector2i RandomGenerator::getIntVector(int minx, int maxx, int miny, int maxy)
{
    m_counter+=2;
    std::uniform_int_distribution<> distx(minx,maxx);
    std::uniform_int_distribution<> disty(miny,maxy);
    return sf::Vector2i(distx(m_generator),disty(m_generator));
}

sf::Vector2f RandomGenerator::getFloatVector(float minx, float maxx, float miny, float maxy)
{
    m_counter+=2;
    std::uniform_real_distribution<> distx(minx,maxx);
    std::uniform_real_distribution<> disty(miny,maxy);
    return sf::Vector2f(distx(m_generator),disty(m_generator));
}

sf::Vector2f RandomGenerator::getNormalizedDirection()
{
    m_counter+=2;
    std::uniform_real_distribution<> dist(-1.0f,1.0f);
    sf::Vector2f direction(dist(m_generator),dist(m_generator));
    Math::normalise(direction);
    return direction;
}

sf::Color RandomGenerator::getColor(unsigned char min, unsigned char max)
{
    m_counter+=3;
    std::uniform_int_distribution<> dist(min,max);
    return sf::Color(dist(m_generator),dist(m_generator),dist(m_generator));
}

unsigned int RandomGenerator::getSeed()
{
    return RandomGenerator::m_seed;
}

void RandomGenerator::setSeed(unsigned int newSeed)
{
    m_seed = newSeed;
    m_generator = std::mt19937(newSeed);
    std::cout << "Set seed to : " << newSeed << " after " << m_counter << " gen " << std::endl;
}
