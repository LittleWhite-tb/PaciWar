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

GameTime::GameTime()
    :m_elapsedTime(sf::Time::Zero)
{
}

void GameTime::update()
{
    m_elapsedTime = m_gameClock.getElapsedTime() - m_previousUpdateTime;
    m_previousUpdateTime = m_gameClock.getElapsedTime();

    m_shouldSpawnEnemy = false;
    if ((m_previousUpdateTime - m_enemySpawnTime).asMilliseconds() > ENEMY_SPAWN_TIME )
    {
        m_enemySpawnTime = m_gameClock.getElapsedTime();
        m_shouldSpawnEnemy = true;
    }

    m_shouldSpawnBarrier = false;
    if ((m_gameClock.getElapsedTime() - m_barrierSpawnTime).asMilliseconds() > BARRIER_SPAWN_TIME )
    {
        m_barrierSpawnTime = m_gameClock.getElapsedTime();
        m_shouldSpawnBarrier = true;
    }
}

int64_t GameTime::getElapsedTime()const
{
    return m_elapsedTime.asMilliseconds();
}

void GameTime::setElapsedTime(int64_t newDeltaTime)
{
    if ( newDeltaTime != 0)
    {
        m_elapsedTime = sf::milliseconds(newDeltaTime);
    }
}
