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

#include "SpawnGrid.hpp"

#include "GameState.hpp"
#include "Objects/Enemy.hpp"

#include "Utils/RandomGenerator.hpp"
#include "Math/Vector2.hpp"

#include <iostream>

SpawnGrid::SpawnGrid(const sf::IntRect& limits)
    :m_lastPointUsed(-1)
{
    // Four corners
    m_spawnPoints.push_back(sf::Vector2f(limits.left,              limits.top));
    m_spawnPoints.push_back(sf::Vector2f(limits.left+limits.width, limits.top));
    m_spawnPoints.push_back(sf::Vector2f(limits.left+limits.width, limits.top+limits.height));
    m_spawnPoints.push_back(sf::Vector2f(limits.left,              limits.top+limits.height));
}

void SpawnGrid::spawnEnemies(GameState& gstate, unsigned int number)
{
    // Select a point
    unsigned int selectedPoint=0;
    do
    {
        selectedPoint = RndGenerators::det_gen.getInt(0,m_spawnPoints.size()-1);
        std::cout << "Try spawn enemy point" << std::endl;
    }while(Math::distance(m_spawnPoints[selectedPoint],gstate.getObjects().getPlayer().getPosition()) < ENEMY_SPAWN_DISTANCE * ENEMY_SPAWN_DISTANCE);

    sf::Vector2f enemyPosition = m_spawnPoints[selectedPoint];

    for (unsigned int i = 0 ; i < number ; i++)
    {
        gstate.getObjects().createEnemy(sf::Vector2f(enemyPosition.x + RndGenerators::det_gen.getInt(-25,25),
                                                     enemyPosition.y + RndGenerators::det_gen.getInt(-25,25)));
        std::cout << "Spawn enemy pos" << std::endl;
    }

    m_lastPointUsed=selectedPoint;
}
