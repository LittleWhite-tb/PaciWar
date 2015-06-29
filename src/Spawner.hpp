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

#ifndef SPAWNER_HPP
#define SPAWNER_HPP

#include "SpawnGrid.hpp"

class GameState;

class Spawner
{
    static constexpr float BARRIER_SPAWN_DISTANCE = 300;

private:
    SpawnGrid m_spawnGrid;

    sf::Vector2f m_gridPosition;
    sf::Vector2f m_gridSize;

    unsigned int m_numberBarrierBySpawn;
    unsigned int m_numberEnemiesBySpawn;

public:
    Spawner(const sf::IntRect &limits);

    void reset();

    void spawnBarriers(GameState &gstate);
    void spawnEnemies(GameState &gstate);
};

#endif
