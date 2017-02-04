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

#include "Collisions/Collider.hpp"
#include "Utils/Palette.hpp"

#include "GameState.hpp"
#include "Settings.hpp"

#include <cassert>
#include <iostream>

void ObjectBank::updateEnemies(GameState& gstate)
{
    using namespace std::chrono;
    steady_clock::time_point updateTime;
    while(!m_threadStop)
    {
        std::vector<Enemy*> enemies = getEnemies();
        auto diff = duration_cast<duration<double>>(steady_clock::now() - updateTime);
        std::for_each(enemies.begin(),enemies.end(), [&diff](Enemy* e){ e->update(diff.count() / 0.1); });
        if (diff.count() > 0.1)
        {
            updateTime = steady_clock::now();
            std::for_each(enemies.begin(),enemies.end(), [&gstate](Enemy* e){ e->update(gstate); });
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
}

template <typename T>
T* ObjectBank::findObject()const {
    for (auto it : m_entitiesPool)
        if (it->getClassId() == T::getName())
            return reinterpret_cast<T*>(it.get());

    return nullptr;
}

template <typename T>
std::vector<T*> ObjectBank::findObjects()const {
    std::vector<T*> items;
    for (auto it : m_entitiesPool)
        if (it->getClassId() == T::getName())
            items.push_back(reinterpret_cast<T*>(it.get()));

    return std::move(items);
}

ObjectBank::ObjectBank(GameState& gstate)
    :m_particleSystemPool(100),
     m_explosionsPool(25),
     m_updateThread(&ObjectBank::updateEnemies, this, std::ref(gstate)),m_threadStop(false)

{
    m_entitiesPool.reserve(10000);
    m_entitiesPool.emplace_back(std::make_shared<Player>());
}

ObjectBank::~ObjectBank()
{
    m_threadStop = true;
    m_updateThread.join();
}

void ObjectBank::createEnemyDeath(const sf::Vector2f& position)
{
    m_entitiesPool.emplace_back(std::make_shared<EnemyDeath>(position));
}

void ObjectBank::createBonus(const sf::Vector2f& position)
{
    m_entitiesPool.emplace_back(std::make_shared<Bonus>(position));
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
    m_entitiesPool.emplace_back(std::make_shared<Barrier>(position));
}

void ObjectBank::createEnemy(const sf::Vector2f& position)
{
    m_entitiesPool.emplace_back(std::make_shared<Enemy>(position));
}

void ObjectBank::draw(sf::RenderWindow& targetWindow)
{
    std::for_each(m_entitiesPool.cbegin(),m_entitiesPool.cend(), [&targetWindow](std::shared_ptr<Entity> e){ e->draw(targetWindow); });

    std::for_each(m_particleSystemPool.cbegin(),m_particleSystemPool.cend(), [&targetWindow](const FixedColorParticleSystem& ps){ ps.draw(targetWindow); });
    std::for_each(m_explosionsPool.cbegin(),m_explosionsPool.cend(), [&targetWindow](const RadialExplosion& re){ re.draw(targetWindow); });

#ifndef NDEBUG
    std::for_each(m_entitiesPool.cbegin(),m_entitiesPool.cend(), [&targetWindow](std::shared_ptr<Entity> e){ e->debugDraw(targetWindow); });
#endif
}

void ObjectBank::update(GameState& gstate)
{
    //std::for_each(m_entitiesPool.begin(),m_entitiesPool.end(), (Enemy* e){ e->update(diff.count() / 0.1); });
    /*
    std::
    m_player.update(gstate);

    std::for_each(m_barriersPool.begin(),m_barriersPool.end(), [&gstate](Barrier& b){ b.update(gstate); });
    std::for_each(m_bonusPool.begin(),m_bonusPool.end(), [&gstate](Bonus& b){ b.update(gstate); });

    std::for_each(m_enemiesDeathPool.begin(),m_enemiesDeathPool.end(), [&gstate](EnemyDeath& ed){ ed.update(gstate); });

    m_enemiesDeathPool.purge(std::bind(&EnemyDeath::isDead,
                                        std::placeholders::_1));
*/
    //if (gstate.getTime().shouldUpdateEnemy())
    {
        std::for_each(m_entitiesPool.begin(),m_entitiesPool.end(), [&gstate](std::shared_ptr<Entity> e){ e->update(gstate); });
    }
    // Position update
    //std::for_each(m_enemiesPool.begin(),m_enemiesPool.end(), [&gstate](Enemy& e){ e.update(gstate.getTime().getLastEnemyUpdateTimeRatio()); });

    int64_t deltaTime = gstate.getTime().getElapsedTime();
    std::for_each(m_particleSystemPool.begin(),m_particleSystemPool.end(), [deltaTime](FixedColorParticleSystem& ps){ ps.update(deltaTime); });
    m_particleSystemPool.purge(std::bind(&FixedColorParticleSystem::isDead,
                                          std::placeholders::_1));

    std::for_each(m_explosionsPool.begin(),m_explosionsPool.end(), [deltaTime](RadialExplosion& re){ re.update(deltaTime); });
    m_explosionsPool.purge(std::bind(&RadialExplosion::isValid,
                                     std::placeholders::_1));

    //applyCollision(gstate);
}

void ObjectBank::applyCollision(GameState& gstate)
{
	bool playerKilled = false;
    unsigned int barriersKilled = 0;
    unsigned int enemiesKilled = 0;
    unsigned int collectedBonusCounter = 0;

    sf::Color rainbowColor = Palette::fromHSV(gstate.getRainbowGradient(),1,1);

    std::vector<Barrier*> barriers = findObjects<Barrier>();
    std::vector<Barrier*>::iterator itBarrier = barriers.begin();
    for ( ; itBarrier != barriers.end() ; ++itBarrier)
    {
        BarrierCollisionResult bcr = Collider::collides(*getPlayer(),*(*itBarrier));
        if ( bcr.collided )
        {
            switch (bcr.getLoser())
            {
                case BarrierCollisionResult::BARRIER:
                    createBonus((*itBarrier)->getLeftEdgePosition());
                    createBonus((*itBarrier)->getRightEdgePosition());
                    createExplosion((*itBarrier)->getPosition());
                    (*itBarrier)->kill();
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

    auto enemies = gstate.getEnemyGrid().getNeighbours(getPlayer()->getPosition());
	for (Enemy* enemy : enemies)
	{
        CollisionResult cr = Collider::collides(*getPlayer(),*enemy);
		if ( cr.collided )
		{
			playerKilled = true;
		}
	}

    std::vector<Bonus*> bonuses = findObjects<Bonus>();
    std::vector<Bonus*>::iterator itBonusses = bonuses.begin();
    for ( ; itBonusses != bonuses.end() ; ++itBonusses )
    {
        CollisionResult cr = Collider::collides(*getPlayer(),*(*itBonusses));
        if ( cr.collided )
        {
            (*itBonusses)->kill();
            collectedBonusCounter++;
        }
    }



    m_entitiesPool.erase(
                std::remove_if(std::begin(m_entitiesPool),
                               std::end(m_entitiesPool),
                               [](std::shared_ptr<Entity> e){return e->isDead();}),
            std::end(m_entitiesPool));

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
    m_entitiesPool.clear();

	m_particleSystemPool.purge();
	m_explosionsPool.purge();
    m_entitiesPool.emplace_back(std::make_shared<Player>());
}

Player* ObjectBank::getPlayer() const {
    Player* pPlayer = findObject<Player>();
    assert(pPlayer);
    return pPlayer;
}

std::vector<Enemy*> ObjectBank::getEnemies() const {
    return findObjects<Enemy>();
}
