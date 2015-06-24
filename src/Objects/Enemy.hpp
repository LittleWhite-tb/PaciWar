#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

#include "ObjectPool.hpp"
#include "Entity.hpp"

class Enemy : public Entity
{
private:
    static constexpr float DEFAULT_SPEED = 0.25f;
    static constexpr float MIN_SPEED = 0.005f;
    static constexpr float BROOD_SPEED_REDUCTION = 0.65f;

    static const sf::Color normalColor;
    static const sf::Color lightColor;

    float m_speed;
    sf::Color m_color;

public:
    Enemy(const sf::Vector2f& position)
        :Entity(position),m_speed(DEFAULT_SPEED),m_color(normalColor) {}
	
    void draw(sf::RenderWindow& window)const;
    void update(GameState& gstate);

    void getBoundingSpheres(BoundingSpheres& boundingSpheres)const;

    static constexpr float SIZE = 2;

    void kill() { m_color = lightColor; }
};

#endif
