#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

#include "EngineParticleSystem.hpp"

class Player : public Entity
{
private:
    static constexpr float SPEED = 0.5f;
    static constexpr float radius = 6.0f;

    EngineParticleSystem m_engineParticles;
	
public:
	Player(const sf::Vector2f& position);
	
	void draw(sf::RenderWindow& window);
    void debugDraw(sf::RenderWindow& window);

    void move(const sf::Vector2f& movement, float time);

    void getBoundingSpheres(BoundingSpheres& boundingSpheres)const;
};

#endif
