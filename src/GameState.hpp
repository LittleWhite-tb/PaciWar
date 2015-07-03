/*
 * PaciWar : Remake of the "pacifism" mode from Geometry Wars 2
 * Copyright (C) 2014-2015 LittleWhite (lw.demoscene@gmail.com)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
    const ObjectBank& getObjects() const { return m_objects; }
    Grid& getEnemyGrid() { return m_enemyGrid; }
    Borders& getBorders() { return m_borders; }
    const Score& getScore()const { return m_score; }
    Score& getScore() { return m_score; }

    sf::Vector2f getInputMovement()const { return m_input.getMovement(); }

    float getRainbowGradient()const { return m_rainbowGradient; }
};

#endif
