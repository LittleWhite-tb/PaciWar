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

#include "GameState.hpp"

#include "Utils/RandomGenerator.hpp"
#include "Input/Replayer.hpp"
#include "Settings.hpp"

GameState::GameState(const Settings& settings)
    :m_settings(settings),m_objects(*this),
     m_enemyGrid(sf::IntRect(-settings.getGameAreaWidth()/2,-settings.getGameAreaHeight()/2, settings.getGameAreaWidth(), settings.getGameAreaHeight())),
     m_borders(sf::IntRect(-settings.getGameAreaWidth()/2,-settings.getGameAreaHeight()/2, settings.getGameAreaWidth(), settings.getGameAreaHeight())),
     m_spawner(m_borders.getRestrictedLimits()),
     m_inputRecorder(nullptr),m_pReplayer(nullptr),
     m_rainbowGradient(0),m_isGameOver(false)
{
    if (settings.isRecording())
    {
        m_inputRecorder.reset(new InputRecorder(settings.getRecordFile(),RndGenerators::det_gen.getSeed()));
    }

    if ( settings.isReplaying())
    {
        m_pReplayer = new Replayer(settings.getReplayFile()),
        m_input.add(std::move(m_pReplayer)); // This take complete ownership
    }
}

void GameState::trySpawn()
{
	if ( m_gameTime.shouldSpawnEnemy())
    {
        m_spawner.spawnEnemies(*this);
    }

    if ( m_gameTime.shouldSpawnBarrier())
    {
        m_spawner.spawnBarriers(*this);
    }
}

void GameState::update()
{
    m_input.update();
    if ( m_settings.isReplaying() )
    {
        m_gameTime.update(m_pReplayer->getDeltaTime());
        if ( !m_pReplayer->enabled() )
        {
            m_isGameOver = true;
        }
    }
    else
    {
        m_gameTime.update();
    }

    if (m_inputRecorder)
    {
        m_inputRecorder->log(*this);
    }

    m_borders.update(m_gameTime.getElapsedTime());

    m_objects.update(*this);
    this->trySpawn();
    
    m_enemyGrid.update(m_objects.getEnemies());

    m_rainbowGradient += m_gameTime.getElapsedTime()*0.03;
}

void GameState::reset()
{
#if GOD_MODE == 0
    m_score.reset();
    m_objects.reset();
    m_spawner.reset();

    if ( m_settings.isReplaying())
    {
        m_pReplayer->restart();
    }
#endif
    m_isGameOver = false;
}
