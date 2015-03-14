#include "SpawnGrid.hpp"

#include "ObjectBank.hpp"
#include "Enemy.hpp"

#include "RandomGenerator.hpp"

SpawnGrid::SpawnGrid(const sf::Vector2f& gridPosition, const sf::Vector2f& gridSize, unsigned int subDivision)
    :m_lastPointUsed(-1)
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

void SpawnGrid::spawnEnemies(ObjectBank& objects, unsigned int number)
{
    // Select a point
    unsigned int selectedPoint=0;
    do
    {
        selectedPoint = RandomGenerator::getInt(0,m_spawnPoints.size()-1);
    }while (m_lastPointUsed == selectedPoint);

    sf::Vector2f enemyPosition = m_spawnPoints[selectedPoint];

    for (unsigned int i = 0 ; i < number ; i++)
    {
        // TODO, this *5 is a bit weird. I have to look why I need it
        Enemy e(sf::Vector2f(enemyPosition.x + (Enemy::SIZE*Enemy::SIZE*5) * (i%3),
                             enemyPosition.y + (Enemy::SIZE*Enemy::SIZE*5) * (i/3)));
        objects.createEnemy(e);
    }

    m_lastPointUsed=selectedPoint;
}
