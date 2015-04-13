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

void GameState::addKill(unsigned int nbEnemies, unsigned int nbBarrier)
{
    m_score += nbBarrier * 25 * m_bonusMultiplier + nbEnemies * 50 * m_bonusMultiplier;
}
