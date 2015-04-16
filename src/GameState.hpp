#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "GameTime.hpp"
#include "ObjectBank.hpp"

class GameState
{
private:
    GameTime m_gameTime;
    ObjectBank m_objects;

    unsigned int m_bonusMultiplier;
    unsigned int m_score;


public:
    GameState();

    void reset();

    void update();

    void addMultiplier(unsigned int number) { m_bonusMultiplier += number; }
    unsigned int getMultiplier()const { return m_bonusMultiplier; }

    void addKill(unsigned int nbEnemies, unsigned int nbBarrier);
    unsigned int getScore()const { return m_score; }

    const GameTime& getTime()const { return m_gameTime; }
    ObjectBank& getObjects() { return m_objects; }
};

#endif
