#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player
{
private:
	sf::Vector2f m_position;
	
public:
	Player(const sf::Vector2f& position);
	
	void draw(sf::RenderWindow& window);
    void move(const sf::Vector2f& movement);
};

#endif
