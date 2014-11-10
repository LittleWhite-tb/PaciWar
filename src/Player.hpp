#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class Player : public Entity
{
private:
    static const float SPEED;
	
public:
	Player(const sf::Vector2f& position);
	
	void draw(sf::RenderWindow& window);
    void move(const sf::Vector2f& movement);
};

#endif
