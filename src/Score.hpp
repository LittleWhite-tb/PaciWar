#ifndef SCORE_HPP
#define SCORE_HPP

class Score
{
    unsigned int m_bonusMultiplier;
    long unsigned int m_score;

public:
    Score();

    void addMultiplier(unsigned int number) { m_bonusMultiplier += number; }
    unsigned int getMultiplier()const { return m_bonusMultiplier; }

    void addKill(unsigned int nbEnemies, unsigned int nbBarrier);
    long unsigned int getScore()const { return m_score; }

    void reset();
};

#endif
