#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Settings.hpp"

#include "GameTime.hpp"
#include "ObjectBank.hpp"
#include "Grid.hpp"
#include "Spawner.hpp"
#include "Objects/Borders.hpp"
#include "Score.hpp"

#include "Input/Input.hpp"

class GameState
{
private:
    const Settings& m_settings;

    GameTime m_gameTime;
    ObjectBank m_objects;
	Grid m_enemyGrid;
    Borders m_borders;
    Spawner m_spawner;
    Score m_score;

    Input m_input;

    float m_rainbowGradient;

    GameState(GameState&)=delete;
    
    void trySpawn();

public:
    GameState(const Settings &settings);

    void reset();

    void update();

    const GameTime& getTime()const { return m_gameTime; }
    ObjectBank& getObjects() { return m_objects; }
    Grid& getEnemyGrid() { return m_enemyGrid; }
    Borders& getBorders() { return m_borders; }
    const Score& getScore()const { return m_score; }
    Score& getScore() { return m_score; }

    sf::Vector2f getInputMovement()const { return m_input.getMovement(); }

    float getRainbowGradient()const { return m_rainbowGradient; }
};

#endif
