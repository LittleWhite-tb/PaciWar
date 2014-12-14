#include "Spawner.hpp"

#include <memory>
#include <vector>

#include "RandomGenerator.hpp"

Spawner::Spawner(const sf::Vector2f& gridPosition, const sf::Vector2f& gridSize)
    :m_spawnGrid(gridPosition, gridSize, 3),
     m_gridPosition(gridPosition),m_gridSize(gridSize),m_numberBarrierBySpawn(1),m_numberEnemiesBySpawn(1),
     m_randomWidthDistribution(gridPosition.x,gridSize.x-1),m_randomHeightDistribution(gridPosition.y,gridSize.y)
{

}

void Spawner::spawnBarriers(const sf::Vector2f& playerPosition, std::vector<std::shared_ptr<Barrier> > &barriers)
{
    for (unsigned int i = 0 ; i < m_numberBarrierBySpawn ; i++)
    {
        sf::Vector2f pos;
        pos.x = m_randomWidthDistribution(RandomGenerator::get());
        pos.y = m_randomHeightDistribution(RandomGenerator::get());

        barriers.push_back(std::make_shared<Barrier>(pos));
    }
}

void Spawner::spawnEnemies(const sf::Vector2f& playerPosition, std::vector<std::shared_ptr<Enemy> > &enemies)
{
    m_spawnGrid.spawnEnemies(playerPosition,enemies,m_numberEnemiesBySpawn);
}
