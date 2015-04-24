#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "GameTime.hpp"
#include "ObjectBank.hpp"
#include "Score.hpp"

#include "Keyboard.hpp"

class GameState
{
private:
    GameTime m_gameTime;
    ObjectBank m_objects;
    Score m_score;

    Keyboard m_keyboard;


public:
    GameState();

    void reset();

    void update();

    const GameTime& getTime()const { return m_gameTime; }
    ObjectBank& getObjects() { return m_objects; }
    Score& getScore() { return m_score; }
    const Keyboard getKeyboard()const { return m_keyboard; }
};

#endif
