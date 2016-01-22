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

#include "EngineParticleSystem.hpp"

#include "Utils/RandomGenerator.hpp"
#include "Utils/Palette.hpp"

EngineParticleSystem::EngineParticleSystem(std::size_t nbMaxParticle)
    :ParticleSystem(sf::Vector2f(0,0),nbMaxParticle),
     m_direction(0,0),m_rainbowGradient(0),m_remaining_birth_time(0)
{

}

void EngineParticleSystem::generateParticle()
{
    sf::Color particleColor = Palette::fromHSV(m_rainbowGradient,1,1);
    sf::Vector2f startDirectionRange = { m_direction.x - PARTICLE_DISPERSION, m_direction.y - PARTICLE_DISPERSION };
    sf::Vector2f endDirectionRange = { m_direction.x + PARTICLE_DISPERSION, m_direction.y + PARTICLE_DISPERSION };

    {
        // Relies on the fact that the pool will never extend
        m_particles.add(m_spawnPoint,
                        RndGenerators::basic_gen.getFloatVector(startDirectionRange.x,endDirectionRange.x,startDirectionRange.y,endDirectionRange.y),
                        particleColor,
                        1000, // Max Life
                        0.1f,0.002f);
    }
}

void EngineParticleSystem::update(const sf::Vector2f &position, const sf::Vector2f &direction, unsigned int time)
{
    ParticleSystem::update(time);

    // Add particules with updated settings
    m_spawnPoint = position;
    m_direction = direction;
    if (!(direction.x == 0 && direction.y == 0)) // Only enabled the direction is valid
    {
        m_rainbowGradient+=time*GRADIENT_SPEED;

        time += m_remaining_birth_time;
        while ( time > BIRTH_PERIOD )
        {
            generateParticle();
            time-=BIRTH_PERIOD;
        }
        m_remaining_birth_time = time;
    }
}
