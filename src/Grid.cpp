#include "Grid.hpp"

#include <cassert>

void Grid::add(const Enemy* enemy)
{
	assert(enemy);
	
	unsigned int x = getXFromPos(enemy->getPosition().x);
	unsigned int y = getYFromPos(enemy->getPosition().y);
	
	if ( x < GRID_WIDTH && y < GRID_HEIGHT )
	{
		m_grid[x][y].emplace_back(enemy);
	}
}

void Grid::update(const Pool<Enemy>& pool)
{
	for(auto& yArrays : m_grid)
	{
		for(auto& arrays : yArrays)
		{
			arrays.erase(arrays.begin(),arrays.end());
		}
	}
	
	for(auto it = pool.cbegin() ; it != pool.cend() ; ++it)
	{
		add(&(*it));
	} 
}

const std::vector<const Enemy*>& Grid::getNeighbours(const Enemy& enemy)
{
	unsigned int x = getXFromPos(enemy.getPosition().x);
	unsigned int y = getYFromPos(enemy.getPosition().y);
	
	if ( x < GRID_WIDTH && y < GRID_HEIGHT )
	{
		return m_grid[x][y];
	}
	else
	{
		static const std::vector<const Enemy*> dummy;
		return dummy;
	}
}
