#include "GameState.hpp"

#include "Settings.hpp"

GameState::GameState(const Settings& settings)
    :m_settings(settings),
     m_enemyGrid(sf::IntRect(-settings.windowWidth/2,-settings.windowHeight/2, settings.windowWidth, settings.windowHeight)),
     m_borders(sf::IntRect(-settings.windowWidth/2,-settings.windowHeight/2, settings.windowWidth, settings.windowHeight)),
     m_spawner(m_borders.getRestrictedLimits()),
     m_rainbowGradient(0)
{
    reset();
}

void GameState::trySpawn()
{
	if ( m_gameTime.shouldSpawnEnemy())
    {
        m_spawner.spawnEnemies(*this);
    }

    if ( m_gameTime.shouldSpawnBarrier())
    {
        m_spawner.spawnBarriers(*this);
    }
}

void GameState::update()
{
    m_gameTime.update();
    m_input.update();
    m_borders.update(m_gameTime.getElapsedTime());

    m_objects.update(*this);
    this->trySpawn();
    
    m_enemyGrid.update(m_objects.getEnemies());

    m_rainbowGradient += m_gameTime.getElapsedTime()*0.03;
}

void GameState::reset()
{
#if GOD_MODE == 0
    m_score.reset();
    m_objects.reset();
    m_spawner.reset();
#endif
}
