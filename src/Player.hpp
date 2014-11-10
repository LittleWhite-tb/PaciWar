#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

#include "Collisions/Sphere.hpp"
#include "Entity.hpp"

class Player : public Entity
{
private:
    static const float SPEED;
    static const float radius;
	
public:
	Player(const sf::Vector2f& position);
	
	void draw(sf::RenderWindow& window);
    void debugDraw(sf::RenderWindow& window);

    void move(const sf::Vector2f& movement);

    Sphere getBoundingSphere()const;
};

#endif
