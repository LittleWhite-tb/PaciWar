#include "GameState.hpp"


GameState::GameState()
{
    reset();
}

void GameState::update()
{
    m_gameTime.update();
    m_keyboard.update();

    m_objects.update(*this);
}

void GameState::reset()
{
    m_score.reset();
}
