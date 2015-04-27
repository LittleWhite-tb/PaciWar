#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "GameTime.hpp"
#include "ObjectBank.hpp"
#include "Borders.hpp"
#include "Score.hpp"

#include "Input.hpp"

class GameState
{
private:
    GameTime m_gameTime;
    ObjectBank m_objects;
    Borders m_borders;
    Score m_score;

    Input m_input;

    GameState(GameState&)=delete;

public:
    GameState();

    void reset();

    void update();

    const GameTime& getTime()const { return m_gameTime; }
    ObjectBank& getObjects() { return m_objects; }
    Borders& getBorders() { return m_borders; }
    Score& getScore() { return m_score; }

    sf::Vector2f getInputMovement()const { return m_input.getMovement(); }
};

#endif
