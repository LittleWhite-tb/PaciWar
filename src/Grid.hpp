#ifndef GRID_HPP
#define GRID_HPP

#include <array>
#include <vector>
#include <iostream>

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

    unsigned int getXFromPos(float posX) { return (posX+m_gameAreaHSize.x)/m_ratio.x; }
	unsigned int getYFromPos(float posY) { return (posY+m_gameAreaHSize.y)/m_ratio.y; }
	
    float getPosFromX(unsigned int x) { return static_cast<float>(x*m_ratio.x)-m_gameAreaHSize.x; }
	float getPosFromY(unsigned int y) { return static_cast<float>(y*m_ratio.y)-m_gameAreaHSize.y; }
	
	void addInZone(const Sphere& sphere, unsigned int x, unsigned int y, std::vector<Enemy*>& enemies);

public:
	Grid(const sf::IntRect& gameArea)
		:m_gameAreaHSize(gameArea.width/2,gameArea.height/2),
		 m_ratio(gameArea.width/GRID_WIDTH, gameArea.height/GRID_HEIGHT) {}
	
	void add(Enemy* enemy);
	void update(Pool<Enemy>& pool);
	const std::vector<Enemy*>& getNeighbours(const Enemy& enemy);
	const std::vector<Enemy*> getNeighbours(const Sphere& sphere);
};

#endif
