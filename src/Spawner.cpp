#include "Spawner.hpp"

#include <memory>
#include <vector>

#include "ObjectBank.hpp"
#include "Barrier.hpp"

#include "RandomGenerator.hpp"

Spawner::Spawner(const sf::Vector2f& gridPosition, const sf::Vector2f& gridSize)
    :m_spawnGrid(gridPosition, gridSize, 3),
     m_gridPosition(gridPosition),m_gridSize(gridSize),m_numberBarrierBySpawn(1),m_numberEnemiesBySpawn(1)
{

}

void Spawner::spawnBarriers(ObjectBank& objects)
{
    // TODO Avoid spawning to close to the player
    for (unsigned int i = 0 ; i < m_numberBarrierBySpawn ; i++)
    {
        sf::Vector2f pos;
        pos.x = RandomGenerator::getInt(m_gridPosition.x,m_gridSize.x-1);
        pos.y = RandomGenerator::getInt(m_gridPosition.y, m_gridSize.y);

        objects.createBarrier(pos);
    }
}

void Spawner::spawnEnemies(ObjectBank& objects)
{
    m_spawnGrid.spawnEnemies(objects,m_numberEnemiesBySpawn);
}
