#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

class Enemy
{
private:
	sf::Vector2f m_position;

public:
	Enemy(const sf::Vector2f& position);
	
	void draw(sf::RenderWindow& window);
};

#endif
