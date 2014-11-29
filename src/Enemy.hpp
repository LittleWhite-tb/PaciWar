#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class Enemy : public Entity
{
private:
    static const float SPEED;

public:
    Enemy(const sf::Vector2f& position)
        :Entity(position) {}
	
	void draw(sf::RenderWindow& window);
    void move(const Entity& target);

    void getBoundingSpheres(BoundingSpheres& boundingSpheres)const;
};

#endif
