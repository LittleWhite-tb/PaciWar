#ifndef OBJECTBANK_HPP
#define OBJECTBANK_HPP

#include "ObjectPool.hpp"

#include "Objects/Player.hpp"
#include "Objects/Barrier.hpp"
#include "Objects/Enemy.hpp"
#include "Objects/EnemyDeath.hpp"
#include "Objects/Bonus.hpp"

#include "Particles/FixedColorParticleSystem.hpp"
#include "Objects/RadialExplosion.hpp"

class GameState;

class ObjectBank
{
private:
	Pool<Barrier> m_barriersPool;
	Pool<Enemy> m_enemiesPool;
    Pool<EnemyDeath> m_enemiesDeathPool;
    Pool<Bonus> m_bonusPool;
	Player m_player;

    Pool<FixedColorParticleSystem> m_particleSystemPool;
    Pool<RadialExplosion> m_explosionsPool;
	
    void applyCollision(GameState& gstate);

    void createEnemyDeath(const sf::Vector2f& position);
    void createBonus(const sf::Vector2f& position);
    void createParticleSystem(const sf::Vector2f& position, const sf::Color &color);
    void createExplosion(const sf::Vector2f& position);

public:
	ObjectBank();

    void createBarrier(const sf::Vector2f& position);
	void createEnemy(const sf::Vector2f& position);

	void draw(sf::RenderWindow& targetWindow);
    void update(GameState& gstate);
    
    void reset();
	
	Player& getPlayer() { return m_player; }
	const Player& getPlayer()const { return m_player; }

    const Pool<Enemy>& getEnemies()const { return m_enemiesPool; }
};

#endif
