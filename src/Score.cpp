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

#include "Score.hpp"

Score::Score()
{
    reset();
}

void Score::addKill(unsigned int nbEnemies, unsigned int nbBarrier)
{
    m_score += nbBarrier * 25 * m_bonusMultiplier +
               nbEnemies * 50 * m_bonusMultiplier;
}

void Score::reset()
{
    m_score=0;
    m_bonusMultiplier = 1;
}
