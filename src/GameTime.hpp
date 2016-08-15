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

#ifndef GAMETIME_HPP
#define GAMETIME_HPP

#include <SFML/Window.hpp>

class GameTime
{
private:
    // All time should be in ms
    sf::Clock m_gameClock;
    int64_t m_elapsedTime;
    int64_t m_previousUpdateTime;

    int64_t m_enemySpawnTime;
    bool m_shouldSpawnEnemy;

    int64_t m_barrierSpawnTime;
    bool m_shouldSpawnBarrier;

    int64_t m_enemyUpdateTime;
    bool m_shouldUpdateEnemy;

    /**
     * Times are in ms
     */
    static constexpr unsigned int ENEMY_SPAWN_TIME = 1000;
    static constexpr unsigned int ENEMY_UPDATE_TIME = 100;
    static constexpr unsigned int BARRIER_SPAWN_TIME = 5000;

    void updateSpawnStates();

public:
    GameTime();

    void update();
    void update(int64_t forcedDeltaTime);
    int64_t getElapsedTime()const;
    float getLastEnemyUpdateTimeRatio()const { return (m_previousUpdateTime - m_enemyUpdateTime)/static_cast<float>(ENEMY_UPDATE_TIME); }

    bool shouldSpawnEnemy()const { return m_shouldSpawnEnemy; }
    bool shouldUpdateEnemy()const { return m_shouldUpdateEnemy; }
    bool shouldSpawnBarrier()const { return m_shouldSpawnBarrier; }
};

#endif
