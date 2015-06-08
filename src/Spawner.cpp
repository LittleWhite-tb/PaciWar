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
            pos = RandomGenerator::getFloatVector(limits.left,limits.left+limits.width,limits.top,limits.top+limits.height);
        }while(Math::distance(pos,gstate.getObjects().getPlayer().getPosition()) < BARRIER_SPAWN_DISTANCE*BARRIER_SPAWN_DISTANCE);
        gstate.getObjects().createBarrier(pos);
    }
}

void Spawner::spawnEnemies(GameState& gstate)
{
    m_spawnGrid.spawnEnemies(gstate,m_numberEnemiesBySpawn);
    m_numberEnemiesBySpawn++;
}
