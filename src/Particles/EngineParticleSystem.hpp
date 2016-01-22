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

#ifndef ENGINEPARTICLESYSTEM_HPP
#define ENGINEPARTICLESYSTEM_HPP

#include "ParticleSystem.hpp"

#include <SFML/Graphics.hpp>

class EngineParticleSystem : public ParticleSystem
{
    static constexpr unsigned int BIRTH_PERIOD = 8; // in milliseconds
    static constexpr float PARTICLE_DISPERSION = 0.45;
    static constexpr float GRADIENT_SPEED = 0.1;

private:
    sf::Vector2f m_direction;

    float m_rainbowGradient;

    unsigned m_remaining_birth_time;

    void generateParticle();

public:
    EngineParticleSystem(std::size_t nbMaxParticle=300);

    void update(const sf::Vector2f& position, const sf::Vector2f& direction, unsigned int time);
};

#endif
