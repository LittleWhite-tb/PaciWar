#ifndef BARRIER_HPP
#define BARRIER_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class Barrier : public Entity
{
public:
    Barrier(const sf::Vector2f& position);
	
	void draw(sf::RenderWindow& window);
};

#endif
