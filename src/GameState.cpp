#include "GameState.hpp"

#include "globals.hpp"

GameState::GameState()
    :m_borders(sf::IntRect(-WIN_WIDTH/2,-WIN_HEIGHT/2, WIN_WIDTH, WIN_HEIGHT)),
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
