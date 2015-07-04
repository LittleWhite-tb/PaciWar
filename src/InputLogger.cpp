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

#include "InputLogger.hpp"

#include "GameState.hpp"

InputLogger::InputLogger(const std::string& outputFile, const unsigned int seed)
    :m_output(outputFile)
{
    m_output << seed << std::endl;
}

void InputLogger::log(const GameState& gstate)
{
    m_output << gstate.getTime().getElapsedTime() << " "
             << gstate.getInputMovement().x << " " << gstate.getInputMovement().y << std::endl;
}
