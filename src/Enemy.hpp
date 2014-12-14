#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <memory>

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
    void move(const std::vector<std::shared_ptr<Enemy> >& enemies, const Entity& target);

    void getBoundingSpheres(BoundingSpheres& boundingSpheres)const;

    static const float SIZE;
};

#endif
