#ifndef SPAWNGRID_HPP
#define SPAWNGRID_HPP

#include <random>

#include <SFML/Graphics.hpp>

#include "Enemy.hpp"

class SpawnGrid
{
private:
    std::vector<sf::Vector2f> m_spawnPoints;
    unsigned int m_lastPointUsed;

    std::uniform_int_distribution<unsigned int> m_randomDistribution;


public:
    SpawnGrid(const sf::Vector2f& gridPosition, const sf::Vector2f& gridSize, unsigned int subDivision);

    void spawnEnemies(const sf::Vector2f& playerPosition, std::vector<Enemy>& enemies, unsigned int number);
};

#endif
