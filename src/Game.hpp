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

#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "UI.hpp"
#include "GameState.hpp"
#include "InputRecorder.hpp"
#include "Settings.hpp"

class Game
{
    static constexpr float VIEW_DELAY_FACTOR = 2.f;

private:
    sf::RenderWindow& m_targetWindow;
    sf::View m_view;

    UI m_userInterface;

    GameState m_state;
    InputRecorder m_inputRecorder;

    void render();
    void update();

    void checkClosure();

public:
    Game(const Settings& settings, sf::RenderWindow& targetWindow);

    bool run();
};

#endif
