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

#include "Grid.hpp"

#include <cassert>
#include <cmath>

#include "Math/Vector2.hpp"

void Grid::add(Enemy* enemy)
{
	assert(enemy);
	
	sf::Vector2f coords = getFromPos(enemy->getPosition());
	
    if ( coords.x > 0 && coords.x < GRID_WIDTH &&
         coords.x > 0 && coords.y < GRID_HEIGHT )
	{
		m_grid[coords.x][coords.y].emplace_back(enemy);
	}
}

void Grid::update(std::vector<Enemy*> pool)
{
	for(auto& yArrays : m_grid)
	{
		for(auto& arrays : yArrays)
		{
			arrays.erase(arrays.begin(),arrays.end());
		}
	}
	
    for(Enemy* e : pool)
	{
        add(e);
	} 
}

const std::vector<Enemy*> Grid::getNeighbours(const Enemy& enemy)
{
    std::vector<Enemy*> enemies;
    enemies.reserve(9*10);
	sf::Vector2f coords = getFromPos(enemy.getPosition());
    if ( coords.x < 0 || coords.x > GRID_WIDTH || // The enemy is outside the grid (happens when game is slowing down)
         coords.y < 0 || coords.y > GRID_HEIGHT )
    {
        return enemies;
    }

    if ( coords.x - 1 > 0)
    {
        if ( coords.y - 1 > 0)
        {
            enemies.insert(enemies.end(), m_grid[coords.x-1][coords.y-1].begin(), m_grid[coords.x-1][coords.y-1].end());
        }

        if ( coords.y < GRID_HEIGHT )
        {
            enemies.insert(enemies.end(), m_grid[coords.x-1][coords.y].begin(), m_grid[coords.x-1][coords.y].end());
        }

        if ( coords.y + 1 < GRID_HEIGHT)
        {
            enemies.insert(enemies.end(), m_grid[coords.x-1][coords.y+1].begin(), m_grid[coords.x-1][coords.y+1].end());
        }
    }

    if ( coords.x < GRID_WIDTH )
    {
        if ( coords.y - 1 > 0)
        {
            enemies.insert(enemies.end(), m_grid[coords.x][coords.y-1].begin(), m_grid[coords.x][coords.y-1].end());
        }

        if ( coords.y < GRID_HEIGHT )
        {
            enemies.insert(enemies.end(), m_grid[coords.x][coords.y].begin(), m_grid[coords.x][coords.y].end());
        }

        if ( coords.y + 1 < GRID_HEIGHT )
        {
            enemies.insert(enemies.end(), m_grid[coords.x][coords.y+1].begin(), m_grid[coords.x][coords.y+1].end());
        }
    }

    if ( coords.x + 1 < GRID_WIDTH )
    {
        if ( coords.y - 1 > 0)
        {
            enemies.insert(enemies.end(), m_grid[coords.x+1][coords.y-1].begin(), m_grid[coords.x+1][coords.y-1].end());
        }

        if ( coords.y < GRID_HEIGHT )
        {
            enemies.insert(enemies.end(), m_grid[coords.x+1][coords.y].begin(), m_grid[coords.x+1][coords.y].end());
        }

        if ( coords.y + 1 < GRID_HEIGHT)
        {
            enemies.insert(enemies.end(), m_grid[coords.x+1][coords.y+1].begin(), m_grid[coords.x+1][coords.y+1].end());
        }
    }
    return enemies;
}

void Grid::addInZone(const Sphere& sphere, unsigned int x, unsigned int y, std::vector<Enemy*>& enemies)
{
	for (std::size_t i = 0 ; i < m_grid[x][y].size() ; i++)
    {
        if ( Math::distance(sphere.center, m_grid[x][y][i]->getPosition()) < sphere.radius*sphere.radius )
        {
            enemies.push_back(m_grid[x][y][i]);
        }
    }
}

const std::vector<Enemy*> Grid::getNeighbours(const Sphere& sphere)
{
    int xwindow = std::ceil((sphere.radius / m_ratio.x)/2);
    int ywindow = std::ceil((sphere.radius / m_ratio.y)/2);
    std::vector<Enemy*> enemies;
    enemies.reserve(xwindow*ywindow*10);
	
	sf::Vector2f coords = getFromPos(sphere.center);

	for (int lx = coords.x-xwindow ; lx < coords.x+xwindow ; lx++ )
	{
		for(int ly = coords.y-ywindow ; ly < coords.y+ywindow ; ly++ )
		{
			if (lx >= 0 && lx < GRID_WIDTH &&
			    ly >= 0 && ly < GRID_HEIGHT)
			{
				addInZone(sphere,lx,ly,enemies);
			}
		}
	}
	
	return enemies;
}
