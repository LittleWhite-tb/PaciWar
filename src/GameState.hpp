#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

class GameState
{
private:
    unsigned int m_bonusMultiplier;
    unsigned int m_score;

public:
    GameState();

    void reset();
    void addMultiplier(unsigned int number) { m_bonusMultiplier += number; }
};

#endif
