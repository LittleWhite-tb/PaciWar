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

#include "Spawner.hpp"

#include <memory>
#include <vector>

#include "GameState.hpp"
#include "Objects/Barrier.hpp"

#include "Utils/RandomGenerator.hpp"
#include "Math/Vector2.hpp"

Spawner::Spawner(const sf::IntRect& limits)
    :m_spawnGrid(limits),m_numberBarrierBySpawn(1),m_numberEnemiesBySpawn(1)
{

}

void Spawner::reset()
{
	m_numberBarrierBySpawn = 1;
	m_numberEnemiesBySpawn = 1;
}

void Spawner::spawnBarriers(GameState& gstate)
{
    sf::IntRect limits = gstate.getBorders().getRestrictedLimits();

    for (unsigned int i = 0 ; i < m_numberBarrierBySpawn ; i++)
    {
        sf::Vector2f pos;
        do
        {
            pos = RndGenerators::det_gen.getFloatVector(limits.left,limits.left+limits.width,limits.top,limits.top+limits.height);
        }while(Math::distance(pos,gstate.getObjects().getPlayer().getPosition()) < BARRIER_SPAWN_DISTANCE*BARRIER_SPAWN_DISTANCE);
        gstate.getObjects().createBarrier(pos);
    }
}

void Spawner::spawnEnemies(GameState& gstate)
{
    m_spawnGrid.spawnEnemies(gstate,m_numberEnemiesBySpawn);
    m_numberEnemiesBySpawn++;
}
