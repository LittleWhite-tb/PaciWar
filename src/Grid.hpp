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

#ifndef GRID_HPP
#define GRID_HPP

#include <array>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Settings.hpp"

#include "Objects/Enemy.hpp"

#define GRID_WIDTH 50
#define GRID_HEIGHT 20

class Grid
{
private:
	std::array<
		std::array<
			std::vector<Enemy*>,
			GRID_HEIGHT>,
		GRID_WIDTH> m_grid;
	sf::Vector2f m_gameAreaHSize;
	sf::Vector2f m_ratio;

    sf::Vector2f getFromPos(const sf::Vector2f pos) 
    {
		sf::Vector2f res; 
		res = pos+m_gameAreaHSize;
		return sf::Vector2f(res.x/m_ratio.x, res.y/m_ratio.y); 
	}
	
    sf::Vector2f getPosFrom(const sf::Vector2f coord) 
    { 
		sf::Vector2f res(coord.x*m_ratio.x,coord.y*m_ratio.y);
		return res-m_gameAreaHSize; 
    }
	
	void addInZone(const Sphere& sphere, unsigned int x, unsigned int y, std::vector<Enemy*>& enemies);

public:
	Grid(const sf::IntRect& gameArea)
		:m_gameAreaHSize(gameArea.width/2,gameArea.height/2),
		 m_ratio(gameArea.width/GRID_WIDTH, gameArea.height/GRID_HEIGHT) {}
	
	void add(Enemy* enemy);
	void update(Pool<Enemy>& pool);
    const std::vector<Enemy *> getNeighbours(const Enemy& enemy);
	const std::vector<Enemy*> getNeighbours(const Sphere& sphere);
};

#endif
