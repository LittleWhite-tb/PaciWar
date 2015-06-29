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

#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "ObjectPool.hpp"

#include "Particle.hpp"

class ParticleSystem
{
protected:
    sf::Vector2f m_spawnPoint;

    Pool<Particle> m_particles;

    virtual void generateParticle();

public:
    ParticleSystem(const sf::Vector2f& position, std::size_t nbMaxParticle=100);
    virtual ~ParticleSystem() {}

    virtual void draw(sf::RenderWindow& window)const;
    virtual void update(unsigned int time);

    std::size_t numberParticlesAlive()const { return m_particles.nbAlive(); }
    bool isDead()const { return m_particles.nbAlive() == 0; }
};

#endif
