#include "ObjectBank.hpp"

#include "Collisions/Collider.hpp"

#include <iostream>

ObjectBank::ObjectBank()
	:m_barriersPool(250),
	 m_enemiesPool(1000),
     m_player(sf::Vector2f(200,100)),
     m_particleSystemPool(100),
     m_explosionsPool(25)
{
	
}

void ObjectBank::createParticleSystem(const sf::Vector2f& position)
{
    ParticleSystem ps(position);
    m_particleSystemPool.add(ps);
}

void ObjectBank::createExplosion(const sf::Vector2f& position)
{
    RadialExplosion explo(position);
    m_explosionsPool.add(explo);
}

void ObjectBank::createBarrier(Barrier& b)
{
	m_barriersPool.add(b);
}

void ObjectBank::createEnemy(Enemy& e)
{
	m_enemiesPool.add(e);
}

void ObjectBank::draw(sf::RenderWindow& targetWindow)
{
	m_barriersPool.update(std::bind(&Entity::draw,
									  std::placeholders::_1,
									  std::ref(targetWindow)));
	m_enemiesPool.update(std::bind(&Entity::draw,
									  std::placeholders::_1,
									  std::ref(targetWindow)));

    m_particleSystemPool.update(std::bind(&ParticleSystem::draw,
                                          std::placeholders::_1,
                                          std::ref(targetWindow)));
    m_explosionsPool.update(std::bind(&RadialExplosion::draw,
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

    m_particleSystemPool.update(std::bind(&ParticleSystem::update,
                                          std::placeholders::_1,
                                          deltaTime));
    m_particleSystemPool.purge(std::bind(&ParticleSystem::isDead,
                                          std::placeholders::_1));

    m_explosionsPool.update(std::bind(&RadialExplosion::update,
                                      std::placeholders::_1,
                                      deltaTime));
    m_explosionsPool.purge(std::bind(&RadialExplosion::isValid,
                                     std::placeholders::_1));

    applyCollision();
}

void ObjectBank::applyCollision()
{
    Pool<Barrier>::iterator itBarrier = m_barriersPool.begin();
    for ( ; itBarrier != m_barriersPool.end() ; ++itBarrier)
    {
        BarrierCollisionResult bcr = Collider::collides(m_player,*itBarrier);
        if ( bcr.collided )
        {
            switch (bcr.getLoser())
            {
                case BarrierCollisionResult::BARRIER:
                    createExplosion(itBarrier->getPosition());
                    itBarrier->kill();
                    break;
                case BarrierCollisionResult::PLAYER:
                    std::cout << "Player kill" << std::endl;
                    break;
            }

            break;
        }
    }

    Pool<Enemy>::iterator itEnemies = m_enemiesPool.begin();
    for ( ; itEnemies != m_enemiesPool.end() ; ++itEnemies )
    {
        Pool<RadialExplosion>::const_iterator itExplosion = m_explosionsPool.begin();
        for ( ; itExplosion != m_explosionsPool.end() ; ++itExplosion )
        {
            CollisionResult cr = Collider::collides(*itEnemies, *itExplosion);
            if ( cr.collided )
            {
                itEnemies->kill();
                createParticleSystem(itEnemies->getPosition());
            }
        }

        if ( ! itEnemies->isDead() )
        {
            CollisionResult cr = Collider::collides(m_player,*itEnemies);
            if ( cr.collided )
            {
                std::cout << "Player kill by enemy" << std::endl;
            }
        }
    }

    // Purge all collided elements
    m_barriersPool.purge(std::bind(&Entity::isDead,
                                   std::placeholders::_1));
    m_enemiesPool.purge(std::bind(&Entity::isDead,
                                  std::placeholders::_1));
}
