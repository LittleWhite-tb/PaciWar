#include "Score.hpp"

Score::Score()
{
    reset();
}

void Score::addKill(unsigned int nbEnemies, unsigned int nbBarrier)
{
    m_score += nbBarrier * 25 * m_bonusMultiplier +
               nbEnemies * 50 * m_bonusMultiplier;
}

void Score::reset()
{
    m_score=0;
    m_bonusMultiplier = 1;
}
