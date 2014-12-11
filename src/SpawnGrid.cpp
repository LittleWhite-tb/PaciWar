#include "SpawnGrid.hpp"

#include "RandomGenerator.hpp"

#include <iostream>

SpawnGrid::SpawnGrid(const sf::Vector2f& gridPosition, const sf::Vector2f& gridSize, unsigned int subDivision)
    :m_randomDistribution(0,subDivision*subDivision-1),m_lastPointUsed(-1)
{
    float width = gridSize.x;
    float height = gridSize.y;

    for (unsigned int x = 0 ; x < subDivision ; x++ )
    {
        for (unsigned int y = 0 ; y < subDivision ; y++)
        {
            m_spawnPoints.push_back(sf::Vector2f(gridPosition.x + (width/subDivision) * x,
                                                 gridPosition.y + (height/subDivision) * y));
        }
    }
}

void SpawnGrid::spawnEnemies(const sf::Vector2f& playerPosition, std::vector<Enemy> &enemies, unsigned int number)
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
        std::cout << "New ennemy X : " << enemyPosition.x + (Enemy::SIZE*Enemy::SIZE) * (i%3) << " ; Y : " <<
                                          enemyPosition.y + (Enemy::SIZE*Enemy::SIZE) * (i/3) << std::endl;
    }

    m_lastPointUsed=selectedPoint;
}
