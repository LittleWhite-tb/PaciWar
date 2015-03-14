#include "ObjectBank.hpp"

ObjectBank::ObjectBank()
	:m_barriersPool(250),
	 m_enemiesPool(1000),
	 m_player(sf::Vector2f(200,100))
{
	
}

void ObjectBank::draw(sf::RenderWindow& targetWindow)
{
	m_barriersPool.update(std::bind(&Entity::draw,
									  std::placeholders::_1,
									  std::ref(targetWindow)));
	m_enemiesPool.update(std::bind(&Entity::draw,
									  std::placeholders::_1,
									  std::ref(targetWindow)));

#ifdef NDEBUG
	m_barriersPool.update(std::bind(&Entity::debugDraw,
									  std::placeholders::_1,
									  std::ref(targetWindow)));
	m_enemiesPool.update(std::bind(&Entity::debugDraw,
									  std::placeholders::_1,
									  std::ref(targetWindow)));
#endif
	m_player.draw(targetWindow);
}

void ObjectBank::update(unsigned int deltaTime)
{
	m_barriersPool.update(std::bind(&Barrier::update,
									  std::placeholders::_1,
									  deltaTime));
	m_enemiesPool.update(std::bind(&Enemy::move,
									  std::placeholders::_1,
									  deltaTime,
									  std::ref(m_player)));
}
