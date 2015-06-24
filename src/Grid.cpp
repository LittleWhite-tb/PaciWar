#include "Grid.hpp"

#include <iostream>
#include <cassert>

#include "Math/Vector2.hpp"

void Grid::add(Enemy* enemy)
{
	assert(enemy);
	
	unsigned int x = getXFromPos(enemy->getPosition().x);
	unsigned int y = getYFromPos(enemy->getPosition().y);
	
	if ( x < GRID_WIDTH && y < GRID_HEIGHT )
	{
		m_grid[x][y].emplace_back(enemy);
	}
}

void Grid::update(Pool<Enemy>& pool)
{
	for(auto& yArrays : m_grid)
	{
		for(auto& arrays : yArrays)
		{
			arrays.erase(arrays.begin(),arrays.end());
		}
	}
	
	for(Pool<Enemy>::iterator it = pool.begin() ; it != pool.end() ; ++it)
	{
		add(&(*it));
	} 
}

const std::vector<Enemy*>& Grid::getNeighbours(const Enemy& enemy)
{
	unsigned int x = getXFromPos(enemy.getPosition().x);
	unsigned int y = getYFromPos(enemy.getPosition().y);
	
	if ( x < GRID_WIDTH && y < GRID_HEIGHT )
	{
		return m_grid[x][y];
	}
	else
	{
		static const std::vector<Enemy*> dummy;
		return dummy;
	}
}

void Grid::addInZone(const Sphere& sphere, unsigned int x, unsigned int y, std::vector<Enemy*>& enemies)
{
	float realX = getPosFromX(x);
	float realY = getPosFromY(y);
	std::cout << "X : " << x << " Y : " << y << " realX : " << realX << " realY : " << realY << std::endl; 
	if ( Math::distance(sphere.center, sf::Vector2f(realX,realY)) < sphere.radius*sphere.radius )
	{
		enemies.insert(enemies.end(),m_grid[x][y].cbegin(),m_grid[x][y].cend());
	}
}

const std::vector<Enemy*> Grid::getNeighbours(const Sphere& sphere)
{
	std::vector<Enemy*> enemies;
	
	int x = getXFromPos(sphere.center.x);
	int y = getYFromPos(sphere.center.y);

	for (int lx = x-3 ; lx < x+3 ; lx++ )
	{
		for(int ly = y-3 ; ly < y+3 ; ly++ )
		{
			if (lx > 0 && lx < GRID_WIDTH &&
			    ly > 0 && ly < GRID_HEIGHT)
			{
				addInZone(sphere,lx,ly,enemies);
			}
		}
	}
	
	return enemies;
}