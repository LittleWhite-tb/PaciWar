#include "GameState.hpp"

GameState::GameState(const Settings& settings)
    :m_settings(settings),
     m_borders(sf::IntRect(-settings.windowWidth/2,-settings.windowHeight/2, settings.windowWidth, settings.windowHeight)),
     m_rainbowGradient(0)
{
    reset();
}

void GameState::update()
{
    m_gameTime.update();
    m_input.update();
    m_borders.update(m_gameTime.getElapsedTime());

    m_objects.update(*this);

    m_rainbowGradient += m_gameTime.getElapsedTime()*0.03;
}

void GameState::reset()
{
    m_score.reset();
}
