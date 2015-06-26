#include "Grid.hpp"

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
	std::vector<Enemy*> enemies;
	
	int x = getXFromPos(sphere.center.x);
	int y = getYFromPos(sphere.center.y);

	int xwindow = ceil((sphere.radius / m_ratio.x)/2);
	int ywindow = ceil((sphere.radius / m_ratio.y)/2);
	for (int lx = x-xwindow ; lx < x+xwindow ; lx++ )
	{
		for(int ly = y-ywindow ; ly < y+ywindow ; ly++ )
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
