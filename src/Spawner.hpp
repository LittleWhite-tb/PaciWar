#ifndef SPAWNER_HPP
#define SPAWNER_HPP

#include "SpawnGrid.hpp"

class GameState;

class Spawner
{
    static constexpr float BARRIER_SPAWN_DISTANCE = 300;

private:
    SpawnGrid m_spawnGrid;

    sf::Vector2f m_gridPosition;
    sf::Vector2f m_gridSize;

    unsigned int m_numberBarrierBySpawn;
    unsigned int m_numberEnemiesBySpawn;

public:
    Spawner(const sf::IntRect &limits);

    void spawnBarriers(GameState &gstate);
    void spawnEnemies(GameState &gstate);
};

#endif
