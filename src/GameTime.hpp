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
    sf::Clock m_gameClock;
    sf::Time m_elapsedTime;
    sf::Time m_previousUpdateTime;

    sf::Time m_enemySpawnTime;
    bool m_shouldSpawnEnemy;

    sf::Time m_barrierSpawnTime;
    bool m_shouldSpawnBarrier;

    /**
     * Times are in ms
     */
    static constexpr unsigned int ENEMY_SPAWN_TIME = 1000;
    static constexpr unsigned int BARRIER_SPAWN_TIME = 5000;

public:
    GameTime();

    void update();
    int64_t getElapsedTime()const;


    bool shouldSpawnEnemy()const { return m_shouldSpawnEnemy; }
    bool shouldSpawnBarrier()const { return m_shouldSpawnBarrier; }
};

#endif
