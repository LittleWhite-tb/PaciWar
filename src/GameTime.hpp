#ifndef GAMETIME_HPP
#define GAMETIME_HPP

#include <SFML/Window.hpp>

class GameTime
{
private:
    sf::Clock m_gameClock;
    sf::Time m_elapsedTime;

    sf::Time m_previousUpdateTime;
    sf::Time m_enemySpawnTime;
    sf::Time m_barrierSpawnTime;

    /**
     * Times are in ms
     */
    static constexpr unsigned int ENEMY_SPAWN_TIME = 1000;
    static constexpr unsigned int BARRIER_SPAWN_TIME = 5000;

public:
    GameTime();

    void update();
    int64_t getElapsedTime()const;


    bool shouldSpawnEnemy();
    bool shouldSpawnBarrier();
};

#endif
