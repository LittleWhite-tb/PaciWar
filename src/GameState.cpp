#include "GameState.hpp"

#include "globals.hpp"

GameState::GameState()
    :m_borders(sf::IntRect(-WIN_WIDTH/2,-WIN_HEIGHT/2, WIN_WIDTH, WIN_HEIGHT))
{
    reset();
}

void GameState::update()
{
    m_gameTime.update();
    m_input.update();

    m_objects.update(*this);
}

void GameState::reset()
{
    m_score.reset();
}
