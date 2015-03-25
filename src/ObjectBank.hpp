#ifndef OBJECTBANK_HPP
#define OBJECTBANK_HPP

#include "ObjectPool.hpp"

#include "Player.hpp"
#include "Barrier.hpp"
#include "Enemy.hpp"

#include "ParticleSystem.hpp"
#include "RadialExplosion.hpp"

class ObjectBank
{
private:
	Pool<Barrier> m_barriersPool;
	Pool<Enemy> m_enemiesPool;
	Player m_player;

    Pool<ExplosionParticleSystem> m_particleSystemPool;
    Pool<RadialExplosion> m_explosionsPool;
	
    void applyCollision();

    void createParticleSystem(const sf::Vector2f& position);
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
