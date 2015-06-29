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

#ifndef SPAWNGRID_HPP
#define SPAWNGRID_HPP

#include <vector>

#include <SFML/Graphics.hpp>

class GameState;

class SpawnGrid
{
    static constexpr float ENEMY_SPAWN_DISTANCE = 300.f;

private:
    std::vector<sf::Vector2f> m_spawnPoints;
    unsigned int m_lastPointUsed;


public:
    SpawnGrid(const sf::IntRect &limits);

    void spawnEnemies(GameState& gstate, unsigned int number);
};

#endif
