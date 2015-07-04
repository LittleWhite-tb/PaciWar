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

#include "Game.hpp"

#include <SFML/Graphics.hpp>

#include "Collisions/Collider.hpp"

#include "Utils/RandomGenerator.hpp"
#if TRACE_MODE == 1
    #include "Tracer.hpp"
#endif
#include "Settings.hpp"

Game::Game(const Settings& settings, sf::RenderWindow& targetWindow)
    :m_targetWindow(targetWindow),m_view(sf::Vector2f(settings.windowWidth/2,settings.windowHeight/2),sf::Vector2f(settings.windowWidth,settings.windowHeight)),m_userInterface(settings.fontPath
#if DEBUG_INFO == 1
    ,settings.debugFontPath
#endif
    ),
     m_state(settings)
#if TRACE_MODE == 1
     ,m_inputLogger(Settings::inputFile,RandomGenerator::getSeed())
#endif
{
}

void Game::render()
{
    m_targetWindow.clear(sf::Color::Black);
    m_targetWindow.setView(m_view);

    m_state.getObjects().draw(m_targetWindow);
    m_state.getBorders().draw(m_targetWindow);


    m_targetWindow.setView(m_targetWindow.getDefaultView());
    m_userInterface.draw(m_targetWindow);

    m_targetWindow.display();
}

void Game::update()
{
    m_state.update();
#if TRACE_MODE == 1
    m_inputLogger.log(m_state);
#endif

    m_view.setCenter((m_state.getObjects().getPlayer().getPosition())/VIEW_DELAY_FACTOR);

    m_userInterface.update(m_state);
}

void Game::checkClosure()
{
    // TODO : Find better to catch window closure, or
    // filter most event to not take too much time here (mouse events)
    sf::Event event;
    while (m_targetWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_targetWindow.close();
            break;
        }

        if (event.type == sf::Event::KeyPressed ||
            event.type == sf::Event::KeyReleased )
        {
            if ( event.key.code == sf::Keyboard::Escape )
            {
                m_targetWindow.close();
                break;
            }
        }
    }
}

bool Game::run()
{
#if TRACE_MODE == 1
    Tracer tracer(Settings::traceFile);
#endif
    while (m_targetWindow.isOpen())
    {
#if TRACE_MODE == 1
        tracer.trace(m_state);
#endif
        render();
        update();

        checkClosure();
    }
    return true;
}
