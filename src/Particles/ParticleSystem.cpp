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

#include "ParticleSystem.hpp"

#include "Utils/RandomGenerator.hpp"

ParticleSystem::ParticleSystem(const sf::Vector2f& position, std::size_t nbMaxParticle)
    :m_spawnPoint(position),m_particles(nbMaxParticle)
{
    // generateParticles();
}

void ParticleSystem::generateParticle()
{
    m_particles.add(m_spawnPoint,
                    RandomGenerator::getNormalizedDirection(),
                    RandomGenerator::getColor(100,255),
                    1000,
                    RandomGenerator::getFloat(0.0,2.0));
}

void ParticleSystem::draw(sf::RenderWindow& window) const
{
    std::for_each(m_particles.cbegin(),m_particles.cend(), [&window](const Particle& p){ p.draw(window); });
}

void ParticleSystem::update(unsigned int time)
{
    std::for_each(m_particles.begin(),m_particles.end(), [time](Particle& p){ p.update(time); });
    m_particles.purge(std::bind(&Particle::isValid,
                                std::placeholders::_1));
}
