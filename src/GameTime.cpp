#include "GameTime.hpp"

GameTime::GameTime()
    :m_elapsedTime(sf::Time::Zero)
{
}

void GameTime::update()
{
    m_elapsedTime = m_gameClock.getElapsedTime() - m_previousUpdateTime;
    m_previousUpdateTime = m_gameClock.getElapsedTime();

    m_shouldSpawnEnemy = false;
    if ((m_previousUpdateTime - m_enemySpawnTime).asMilliseconds() > ENEMY_SPAWN_TIME )
    {
        m_enemySpawnTime = m_gameClock.getElapsedTime();
        m_shouldSpawnEnemy = true;
    }

    m_shouldSpawnBarrier = false;
    if ((m_gameClock.getElapsedTime() - m_barrierSpawnTime).asMilliseconds() > BARRIER_SPAWN_TIME )
    {
        m_barrierSpawnTime = m_gameClock.getElapsedTime();
        m_shouldSpawnBarrier = true;
    }
}

int64_t GameTime::getElapsedTime()const
{
    return m_elapsedTime.asMilliseconds();
}
