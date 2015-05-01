#ifndef SPAWNGRID_HPP
#define SPAWNGRID_HPP

#include <vector>

#include <SFML/Graphics.hpp>

class GameState;

class SpawnGrid
{
    static constexpr float ENEMY_SPAWN_DISTANCE = 300.f;

private:
    std::vector<sf::Vector2f> m_spawnPoints;
    unsigned int m_lastPointUsed;


public:
    SpawnGrid(const sf::IntRect &limits);

    void spawnEnemies(GameState& gstate, unsigned int number);
};

#endif
