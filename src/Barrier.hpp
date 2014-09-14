#ifndef BARRIER_HPP
#define BARRIER_HPP

#include <SFML/Graphics.hpp>

class Barrier
{
private:
	sf::Vector2f m_position;

public:
	Barrier(const sf::Vector2f& position);
	
	void draw(sf::RenderWindow& window);
};

#endif
