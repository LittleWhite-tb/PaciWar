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

#include "Replayer.hpp"

#include "Utils/RandomGenerator.hpp"

#include <iostream>

Replayer::Replayer(const std::string& inputFile)
    :m_input(inputFile),m_lastUpdate(0),m_accum(0),m_lastRead(0,sf::Vector2f()),m_isFirstLine(true)
{
    unsigned int seed;
    m_input >> seed;
    RndGenerators::det_gen.setSeed(seed);
}

Replayer::DataLine Replayer::readLine()
{
    Replayer::DataLine data;
    float x=0,y=0;
    m_input >> data.first >> x >> y;
    data.second = sf::Vector2f(x,y);
    return data;
}

#if 0
void Replayer::update()
{
    if ( m_isFirstLine )
    {
        this->readLine();
        m_clock.restart();
        m_isFirstLine = false;
        return;
    }

    int64_t deltaTime  = m_clock.getElapsedTime().asMilliseconds() - m_lastUpdate;
    m_accum += deltaTime;

    //std::cout << "DeltaTime : " << deltaTime << std::endl;

    while (m_accum > m_lastRead.first && m_input)
    {
        m_lastRead = this->readLine();
        m_accum -= m_lastRead.first;
        //std::cout << "Read : " << m_lastRead.first << " against dt : " << deltaTime << " file is " << (bool)m_input << std::endl;
    }

    m_lastUpdate = m_clock.getElapsedTime().asMilliseconds();
    if (!m_input)
    {
        m_isEnabled=false;
    }
}
#endif

void Replayer::update()
{
    m_lastRead = this->readLine();
    if (!m_input)
    {
        m_isEnabled = false;
        m_lastRead.first = 0;
    }
}

sf::Vector2f Replayer::getMovement()const
{
    return m_lastRead.second;
}

int64_t Replayer::getDeltaTime()const
{
    return m_lastRead.first;
}

void Replayer::start()
{
    m_clock.restart();
}

void Replayer::restart()
{
    m_input.seekg(std::ios_base::beg);
}
