#include "SpawnGrid.hpp"

#include "GameState.hpp"
#include "Enemy.hpp"

#include "RandomGenerator.hpp"
#include "SFML/Vector2Utils.hpp"

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
        selectedPoint = RandomGenerator::getInt(0,m_spawnPoints.size()-1);
    }while(SFMLUtils::distance(m_spawnPoints[selectedPoint],gstate.getObjects().getPlayer().getPosition()) < ENEMY_SPAWN_DISTANCE * ENEMY_SPAWN_DISTANCE);

    sf::Vector2f enemyPosition = m_spawnPoints[selectedPoint];

    for (unsigned int i = 0 ; i < number ; i++)
    {
        gstate.getObjects().createEnemy(sf::Vector2f(enemyPosition.x + RandomGenerator::getInt(-25,25),
                                                     enemyPosition.y + RandomGenerator::getInt(-25,25)));
    }

    m_lastPointUsed=selectedPoint;
}
