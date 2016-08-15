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

#include <thread>

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

    std::thread m_updateThread;
    bool m_threadStop;
	
    void applyCollision(GameState& gstate);

    void createEnemyDeath(const sf::Vector2f& position);
    void createBonus(const sf::Vector2f& position);
    void createParticleSystem(const sf::Vector2f& position, const sf::Color &color);
    void createExplosion(const sf::Vector2f& position);

    void updateEnemies(GameState& gstate);

public:
    ObjectBank(GameState &gstate);
    ~ObjectBank();

    void createBarrier(const sf::Vector2f& position);
	void createEnemy(const sf::Vector2f& position);

	void draw(sf::RenderWindow& targetWindow);
    void update(GameState& gstate);
    
    void reset();
	
	Player& getPlayer() { return m_player; }
	const Player& getPlayer()const { return m_player; }

    const Pool<Enemy>& getEnemies()const { return m_enemiesPool; }
    Pool<Enemy>& getEnemies() { return m_enemiesPool; }
};

#endif
