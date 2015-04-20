#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class Enemy : public Entity
{
private:
    static constexpr float SPEED = 0.25f;

public:
    Enemy(const sf::Vector2f& position)
        :Entity(position) {}
	
	void draw(sf::RenderWindow& window);
    void update(GameState& gstate);

    void getBoundingSpheres(BoundingSpheres& boundingSpheres)const;

    static constexpr float SIZE = 2;
};

#endif
