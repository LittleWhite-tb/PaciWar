#include "GameTime.hpp"

GameTime::GameTime()
    :m_elapsedTime(sf::Time::Zero)
{
}

void GameTime::update()
{
    m_elapsedTime = m_gameClock.getElapsedTime() - m_previousUpdateTime;
    m_previousUpdateTime = m_gameClock.getElapsedTime();
}

int64_t GameTime::getElapsedTime()const
{
    return m_elapsedTime.asMilliseconds();
}

bool GameTime::shouldSpawnEnemy()
{
    if ((m_gameClock.getElapsedTime() - m_enemySpawnTime).asMilliseconds() > ENEMY_SPAWN_TIME )
    {
        m_enemySpawnTime = m_gameClock.getElapsedTime();
        return true;
    }
    return false;
}

bool GameTime::shouldSpawnBarrier()
{
    if ((m_gameClock.getElapsedTime() - m_barrierSpawnTime).asMilliseconds() > BARRIER_SPAWN_TIME )
    {
        m_barrierSpawnTime = m_gameClock.getElapsedTime();
        return true;
    }
    return false;
}
