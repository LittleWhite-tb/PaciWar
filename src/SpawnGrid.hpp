#ifndef SPAWNGRID_HPP
#define SPAWNGRID_HPP

#include <vector>

#include <SFML/Graphics.hpp>

class ObjectBank;

class SpawnGrid
{
private:
    std::vector<sf::Vector2f> m_spawnPoints;
    unsigned int m_lastPointUsed;


public:
    SpawnGrid(const sf::Vector2f& gridPosition, const sf::Vector2f& gridSize, unsigned int subDivision);

    void spawnEnemies(ObjectBank& objects, unsigned int number);
};

#endif
