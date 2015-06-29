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

#ifndef SCORE_HPP
#define SCORE_HPP

class Score
{
    unsigned int m_bonusMultiplier;
    long unsigned int m_score;

public:
    Score();

    void addMultiplier(unsigned int number) { m_bonusMultiplier += number; }
    unsigned int getMultiplier()const { return m_bonusMultiplier; }

    void addKill(unsigned int nbEnemies, unsigned int nbBarrier);
    long unsigned int getScore()const { return m_score; }

    void reset();
};

#endif
