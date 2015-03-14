#ifndef OBJECTBANK_HPP
#define OBJECTBANK_HPP

#include "ObjectPool.hpp"

#include "Player.hpp"
#include "Barrier.hpp"
#include "Enemy.hpp"

class ObjectBank
{
private:
	Pool<Barrier> m_barriersPool;
	Pool<Enemy> m_enemiesPool;
	Player m_player;
	
public:
	ObjectBank();
	
	void createBarrier(Barrier& b);
	void createEnemy(Enemy& e);

	void draw(sf::RenderWindow& targetWindow);
	void update(unsigned int deltaTime);
	
	Player& getPlayer() { return m_player; }
	const Player& getPlayer()const { return m_player; }
};

#endif
