/*
 * PaciWar : Remake of the "pacifism" mode from Geometry Wars 2
 * Copyright (C) 2014-2015 LittleWhite (lw.demoscene@gmail.com)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ObjectBank.hpp"

#include "EnemyGroup.hpp"

#include "Collisions/Collider.hpp"
#include "Utils/Palette.hpp"

#include "GameState.hpp"
#include "Settings.hpp"

#include <iostream>

void ObjectBank::updateEnemies(GameState& gstate)
{
    using namespace std::chrono;
    steady_clock::time_point updateTime;

    EnemyGroups enemyGroups;

    while(!m_threadStop)
    {
        auto diff = duration_cast<duration<double>>(steady_clock::now() - updateTime);
        std::for_each(m_enemiesPool.begin(),m_enemiesPool.end(), [&diff](Enemy& e){ e.update(diff.count() / 0.1); });
        if (diff.count() > 0.1)
        {
            updateTime = steady_clock::now();
            // std::for_each(m_enemiesPool.begin(),m_enemiesPool.end(), [&gstate](Enemy& e){ e.update(gstate); });
            enemyGroups.reset();
            std::for_each(m_enemiesPool.begin(),m_enemiesPool.end(), [&enemyGroups](Enemy& e){ enemyGroups.classify(e); });
            enemyGroups.update(gstate);
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
}

ObjectBank::ObjectBank(GameState& gstate)
	:m_barriersPool(250),
     m_enemiesPool(MAX_ENEMY_NUMBER),m_enemiesDeathPool(1000),m_bonusPool(1000),
     m_particleSystemPool(100),
     m_explosionsPool(25),
     m_updateThread(&ObjectBank::updateEnemies, this, std::ref(gstate)),m_threadStop(false)

{

}

ObjectBank::~ObjectBank()
{
    m_threadStop = true;
    m_updateThread.join();
}

void ObjectBank::createEnemyDeath(const sf::Vector2f& position)
{
    m_enemiesDeathPool.add(position);
}

void ObjectBank::createBonus(const sf::Vector2f& position)
{
    m_bonusPool.add(position);
}

void ObjectBank::createParticleSystem(const sf::Vector2f& position, const sf::Color& color)
{
    m_particleSystemPool.add(position,color);
}

void ObjectBank::createExplosion(const sf::Vector2f& position)
{
    m_explosionsPool.add(position);
}

void ObjectBank::createBarrier(const sf::Vector2f& position)
{
	m_barriersPool.add(position);
}

void ObjectBank::createEnemy(const sf::Vector2f& position)
{
	m_enemiesPool.add(position);
}

void ObjectBank::draw(sf::RenderWindow& targetWindow)
{
    std::for_each(m_barriersPool.cbegin(),m_barriersPool.cend(), [&targetWindow](const Barrier& b){ b.draw(targetWindow); });
    std::for_each(m_enemiesPool.cbegin(),m_enemiesPool.cend(), [&targetWindow](const Enemy& e){ e.draw(targetWindow); });
    std::for_each(m_enemiesDeathPool.cbegin(),m_enemiesDeathPool.cend(), [&targetWindow](const EnemyDeath& ed){ ed.draw(targetWindow); });
    std::for_each(m_bonusPool.cbegin(),m_bonusPool.cend(), [&targetWindow](const Bonus& b){ b.draw(targetWindow); });

    std::for_each(m_particleSystemPool.cbegin(),m_particleSystemPool.cend(), [&targetWindow](const FixedColorParticleSystem& ps){ ps.draw(targetWindow); });
    std::for_each(m_explosionsPool.cbegin(),m_explosionsPool.cend(), [&targetWindow](const RadialExplosion& re){ re.draw(targetWindow); });

#ifndef NDEBUG
    std::for_each(m_barriersPool.cbegin(),m_barriersPool.cend(), [&targetWindow](const Barrier& b){ b.debugDraw(targetWindow); });
    std::for_each(m_enemiesPool.cbegin(),m_enemiesPool.cend(), [&targetWindow](const Enemy& e){ e.debugDraw(targetWindow); });
    std::for_each(m_bonusPool.cbegin(),m_bonusPool.cend(), [&targetWindow](const Bonus& b){ b.debugDraw(targetWindow); });

    m_player.debugDraw(targetWindow);
#endif

	m_player.draw(targetWindow);
}

void ObjectBank::update(GameState& gstate)
{
    m_player.update(gstate);

    std::for_each(m_barriersPool.begin(),m_barriersPool.end(), [&gstate](Barrier& b){ b.update(gstate); });
    std::for_each(m_bonusPool.begin(),m_bonusPool.end(), [&gstate](Bonus& b){ b.update(gstate); });

    std::for_each(m_enemiesDeathPool.begin(),m_enemiesDeathPool.end(), [&gstate](EnemyDeath& ed){ ed.update(gstate); });
    m_enemiesDeathPool.purge(std::bind(&EnemyDeath::isDead,
                                        std::placeholders::_1));

    int64_t deltaTime = gstate.getTime().getElapsedTime();
    std::for_each(m_particleSystemPool.begin(),m_particleSystemPool.end(), [deltaTime](FixedColorParticleSystem& ps){ ps.update(deltaTime); });
    m_particleSystemPool.purge(std::bind(&FixedColorParticleSystem::isDead,
                                          std::placeholders::_1));

    std::for_each(m_explosionsPool.begin(),m_explosionsPool.end(), [deltaTime](RadialExplosion& re){ re.update(deltaTime); });
    m_explosionsPool.purge(std::bind(&RadialExplosion::isValid,
                                     std::placeholders::_1));

    applyCollision(gstate);
}

void ObjectBank::applyCollision(GameState& gstate)
{
	bool playerKilled = false;
    unsigned int barriersKilled = 0;
    unsigned int enemiesKilled = 0;
    unsigned int collectedBonusCounter = 0;

    sf::Color rainbowColor = Palette::fromHSV(gstate.getRainbowGradient(),1,1);

    Pool<Barrier>::iterator itBarrier = m_barriersPool.begin();
    for ( ; itBarrier != m_barriersPool.end() ; ++itBarrier)
    {
        BarrierCollisionResult bcr = Collider::collides(m_player,*itBarrier);
        if ( bcr.collided )
        {
            switch (bcr.getLoser())
            {
                case BarrierCollisionResult::BARRIER:
                    createBonus(itBarrier->getLeftEdgePosition());
                    createBonus(itBarrier->getRightEdgePosition());
                    createExplosion(itBarrier->getPosition());
                    itBarrier->kill();
                    barriersKilled+=2;

                    gstate.getBorders().impulse(rainbowColor);
                    break;
                case BarrierCollisionResult::PLAYER:
                    playerKilled = true;
                    break;
            }

            break;
        }
    }

	Pool<RadialExplosion>::const_iterator itExplosion = m_explosionsPool.begin();
	for ( ; itExplosion != m_explosionsPool.end() ; ++itExplosion )
	{
		auto enemies = gstate.getEnemyGrid().getNeighbours(Sphere(itExplosion->getCenter(),itExplosion->getRadius()));
		for (Enemy* enemy : enemies)
		{
			enemy->kill();
			createEnemyDeath(enemy->getPosition());
			createBonus(enemy->getPosition());
			createParticleSystem(enemy->getPosition(),rainbowColor);
			enemiesKilled +=1;
		}
	}

    auto enemies = gstate.getEnemyGrid().getNeighbours(m_player.getPosition());
	for (Enemy* enemy : enemies)
	{
		CollisionResult cr = Collider::collides(m_player,*enemy);
		if ( cr.collided )
		{
			playerKilled = true;
		}
	}

    Pool<Bonus>::iterator itBonusses = m_bonusPool.begin();
    for ( ; itBonusses != m_bonusPool.end() ; ++itBonusses )
    {
        CollisionResult cr = Collider::collides(m_player,*itBonusses);
        if ( cr.collided )
        {
            itBonusses->kill();
            collectedBonusCounter++;
        }
    }


    // Purge all collided elements
    m_barriersPool.purge(std::bind(&Entity::isDead,
                                   std::placeholders::_1));
    m_enemiesPool.purge(std::bind(&Entity::isDead,
                                  std::placeholders::_1));
    m_bonusPool.purge(std::bind(&Bonus::isDead,
                                std::placeholders::_1));

    gstate.getScore().addMultiplier(collectedBonusCounter);
    gstate.getScore().addKill(enemiesKilled,barriersKilled);
    
    if (playerKilled)
    {
        gstate.gameOver();
        gstate.reset();
	}
}

void ObjectBank::reset()
{
	m_barriersPool.purge();
	m_enemiesPool.purge();
	m_enemiesDeathPool.purge();
	m_bonusPool.purge();
	m_particleSystemPool.purge();
	m_explosionsPool.purge();
	m_player = Player();
}
