#include "GameState.hpp"


GameState::GameState()
{
    reset();
}

void GameState::reset()
{
    m_bonusMultiplier=1;
    m_score = 0;
}
