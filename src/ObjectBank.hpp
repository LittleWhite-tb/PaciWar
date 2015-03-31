#ifndef OBJECTBANK_HPP
#define OBJECTBANK_HPP

#include "ObjectPool.hpp"

#include "Player.hpp"
#include "Barrier.hpp"
#include "Enemy.hpp"
#include "Bonus.hpp"

#include "FixedColorParticleSystem.hpp"
#include "RadialExplosion.hpp"

class ObjectBank
{
private:
	Pool<Barrier> m_barriersPool;
	Pool<Enemy> m_enemiesPool;
    Pool<Bonus> m_bonusPool;
	Player m_player;

    Pool<FixedColorParticleSystem> m_particleSystemPool;
    Pool<RadialExplosion> m_explosionsPool;

    float m_rainbowGradient; // Hack since all enemies are not dying at the same time, but we want same color for particles
	
    void applyCollision();

    void createBonus(const sf::Vector2f& position);
    void createParticleSystem(const sf::Vector2f& position, const sf::Color &color);
    void createExplosion(const sf::Vector2f& position);

public:
	ObjectBank();

    void createBarrier(const sf::Vector2f& position);
	void createEnemy(const sf::Vector2f& position);

	void draw(sf::RenderWindow& targetWindow);
	void update(unsigned int deltaTime);
	
	Player& getPlayer() { return m_player; }
	const Player& getPlayer()const { return m_player; }
};

#endif
