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

#include "GameTime.hpp"

#include <iostream>

GameTime::GameTime()
    :m_elapsedTime(0),m_previousUpdateTime(0),m_enemySpawnTime(0),m_barrierSpawnTime(0)
{
}

void GameTime::updateSpawnStates()
{
    // From here 'm_previousUpdateTime' correspond to the actual time
    m_shouldSpawnEnemy = false;
    if (m_previousUpdateTime - m_enemySpawnTime > ENEMY_SPAWN_TIME )
    {
        std::cout << "Enemy Spawn time : " << m_enemySpawnTime << std::endl;
        m_enemySpawnTime = m_previousUpdateTime;
        m_shouldSpawnEnemy = true;
    }

    m_shouldSpawnBarrier = false;
    if (m_previousUpdateTime - m_barrierSpawnTime > BARRIER_SPAWN_TIME )
    {
        std::cout << "Barrier Spawn time : " << m_enemySpawnTime << std::endl;
        m_barrierSpawnTime = m_previousUpdateTime;
        m_shouldSpawnBarrier = true;
    }
}

void GameTime::update()
{
    int64_t clockTime = m_gameClock.getElapsedTime().asMilliseconds();
    m_elapsedTime =  clockTime - m_previousUpdateTime;
    m_previousUpdateTime = clockTime;

    this->updateSpawnStates();
}

void GameTime::update(int64_t forcedDeltaTime)
{
    m_elapsedTime = forcedDeltaTime;
    m_previousUpdateTime = m_previousUpdateTime + m_elapsedTime;

    this->updateSpawnStates();
}

int64_t GameTime::getElapsedTime()const
{
    return m_elapsedTime;
}
