#ifndef SPAWNER_HPP
#define SPAWNER_HPP

#include "SpawnGrid.hpp"
#include "Barrier.hpp"

class Spawner
{
private:
    SpawnGrid m_spawnGrid;

    sf::Vector2f m_gridPosition;
    sf::Vector2f m_gridSize;

    unsigned int m_numberBarrierBySpawn;
    unsigned int m_numberEnemiesBySpawn;

public:
    Spawner(const sf::Vector2f& gridPosition, const sf::Vector2f& gridSize);

    void spawnBarriers(const sf::Vector2f& playerPosition, std::vector<std::shared_ptr<Barrier> > &barriers);
    void spawnEnemies(const sf::Vector2f& playerPosition, std::vector<std::shared_ptr<Enemy> > &enemies);
};

#endif
