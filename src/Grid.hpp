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
			std::vector<const Enemy*>,
			GRID_HEIGHT>,
		GRID_WIDTH> m_grid;
	int m_gameAreaHWidth;
	int m_gameAreaHHeight;

	unsigned int getXFromPos(float posX) { return (posX+m_gameAreaHWidth)/GRID_WIDTH; }
	unsigned int getYFromPos(float posY) { return (posY+m_gameAreaHHeight)/GRID_HEIGHT; }

public:
	Grid(const sf::IntRect& gameArea)
		:m_gameAreaHWidth(gameArea.width/2),
		 m_gameAreaHHeight(gameArea.height/2) {};
	
	void add(const Enemy* enemy);
	void update(const Pool<Enemy>& pool);
	const std::vector<const Enemy*>& getNeighbours(const Enemy& enemy);
};

#endif
