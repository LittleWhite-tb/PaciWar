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

#if REPLAY_MODE == 1
    #include "Input/Replayer.hpp"
#endif
#include "Utils/RandomGenerator.hpp"
#include "Settings.hpp"

GameState::GameState(const Settings& settings)
    :m_settings(settings),
     m_enemyGrid(sf::IntRect(-settings.windowWidth/2,-settings.windowHeight/2, settings.windowWidth, settings.windowHeight)),
     m_borders(sf::IntRect(-settings.windowWidth/2,-settings.windowHeight/2, settings.windowWidth, settings.windowHeight)),
     m_spawner(m_borders.getRestrictedLimits()),
#if RECORD_MODE == 1
     m_inputRecorder(Settings::recordFile,RndGenerators::det_gen.getSeed()),
#endif
#if REPLAY_MODE == 1
     m_pReplayer(new Replayer(Settings::replayFile)),
#endif
     m_rainbowGradient(0)
{
    reset();
#if REPLAY_MODE == 1
    m_input.add(m_pReplayer);
#endif
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
#if REPLAY_MODE == 1
    m_gameTime.update(m_pReplayer->getDeltaTime());
#else
    m_gameTime.update();
#endif
#if RECORD_MODE == 1
    m_inputRecorder.log(*this);
#endif
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
#endif
}
