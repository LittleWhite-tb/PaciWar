#include "Grid.hpp"

#include <cassert>

#include "Math/Vector2.hpp"

void Grid::add(Enemy* enemy)
{
	assert(enemy);
	
	sf::Vector2f coords = getFromPos(enemy->getPosition());
	
	if ( coords.x < GRID_WIDTH && coords.y < GRID_HEIGHT )
	{
		m_grid[coords.x][coords.y].emplace_back(enemy);
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

const std::vector<Enemy*> Grid::getNeighbours(const Enemy& enemy)
{
    std::vector<Enemy*> enemies;
    enemies.reserve(9*10);
	sf::Vector2f coords = getFromPos(enemy.getPosition());

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
    int xwindow = ceil((sphere.radius / m_ratio.x)/2);
    int ywindow = ceil((sphere.radius / m_ratio.y)/2);
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
