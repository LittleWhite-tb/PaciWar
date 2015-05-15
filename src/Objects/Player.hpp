#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

#include "Particles/EngineParticleSystem.hpp"

class Player : public Entity
{
private:
    static constexpr float SPEED = 0.5f;
    static constexpr float radius = 6.0f;

    EngineParticleSystem m_engineParticles;
	
public:
    Player();
	
    void draw(sf::RenderWindow& window)const;
    void debugDraw(sf::RenderWindow& window)const;

    void update(GameState& gstate);

    void getBoundingSpheres(BoundingSpheres& boundingSpheres)const;
};

#endif
