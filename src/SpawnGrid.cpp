#include "SpawnGrid.hpp"

#include "RandomGenerator.hpp"

SpawnGrid::SpawnGrid(const sf::Vector2f& gridSize, unsigned int subDivision)
    :m_gridSize(gridSize),m_randomDistribution(0,subDivision*subDivision),m_lastPointUsed(-1)
{
    for (unsigned int x = 0 ; x < subDivision ; x++ )
    {
        for (unsigned int y = 0 ; y < subDivision ; y++)
        {
            m_spawnPoints.push_back(sf::Vector2f(gridSize.x/subDivision * x, gridSize.y/subDivision * y));
        }
    }
}

void SpawnGrid::spawnEnemies(const sf::Vector2f &playerPosition, std::vector<Enemy> &enemies, unsigned int number)
{
    // Select a point
    unsigned int selectedPoint=0;
    do
    {
        selectedPoint = m_randomDistribution(RandomGenerator::get());
    }while (m_lastPointUsed == selectedPoint);

    sf::Vector2f enemyPosition = m_spawnPoints[selectedPoint];
    for (unsigned int i = 0 ; i < number ; i++)
    {
        enemies.push_back(Enemy(sf::Vector2f(enemyPosition.x + (Enemy::SIZE*Enemy::SIZE) * (i%3),
                                             enemyPosition.y + (Enemy::SIZE*Enemy::SIZE) * (i/3))));
    }

    m_lastPointUsed=selectedPoint;
}
