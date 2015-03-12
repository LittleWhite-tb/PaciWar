#include "Spawner.hpp"

#include <memory>
#include <vector>

#include "RandomGenerator.hpp"

Spawner::Spawner(const sf::Vector2f& gridPosition, const sf::Vector2f& gridSize)
    :m_spawnGrid(gridPosition, gridSize, 3),
     m_gridPosition(gridPosition),m_gridSize(gridSize),m_numberBarrierBySpawn(1),m_numberEnemiesBySpawn(1)
{

}

void Spawner::spawnBarriers(const sf::Vector2f& playerPosition, std::vector<std::shared_ptr<Barrier> > &barriers)
{
    // TODO Avoid spawning to close to the player
    for (unsigned int i = 0 ; i < m_numberBarrierBySpawn ; i++)
    {
        sf::Vector2f pos;
        pos.x = RandomGenerator::getInt(m_gridPosition.x,m_gridSize.x-1);
        pos.y = RandomGenerator::getInt(m_gridPosition.y, m_gridSize.y);

        barriers.push_back(std::make_shared<Barrier>(pos));
    }
}

void Spawner::spawnEnemies(const sf::Vector2f& playerPosition, std::vector<std::shared_ptr<Enemy> > &enemies)
{
    m_spawnGrid.spawnEnemies(playerPosition,enemies,m_numberEnemiesBySpawn);
}
