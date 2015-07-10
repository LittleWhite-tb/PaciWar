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

#include "Momentum.hpp"

#include "Math/Vector2.hpp"
#include "Utils/RandomGenerator.hpp"

Momentum::Momentum()
    :m_direction(RndGenerators::det_gen.getNormalizedDirection()),
     m_moveSpeed(RndGenerators::det_gen.getFloat(0,0.1f)),
     m_rotationSpeed(RndGenerators::det_gen.getFloat(0,m_moveSpeed))
{
    Math::normalise(m_direction);
}

Momentum::Momentum(float maxMoveSpeed, float maxRotationSpeed)
    :m_direction(RndGenerators::det_gen.getNormalizedDirection()),
     m_moveSpeed(RndGenerators::det_gen.getFloat(0,maxMoveSpeed)),
     m_rotationSpeed(RndGenerators::det_gen.getFloat(0,maxRotationSpeed))
{
    Math::normalise(m_direction);
}

Momentum::Momentum(const sf::Vector2f& direction, float moveSpeed, float rotationSpeed)
    :m_direction(direction),m_moveSpeed(moveSpeed),m_rotationSpeed(rotationSpeed)
{

}

void Momentum::update(sf::Vector2f& position, float& rotation, unsigned int deltaTime)
{
    position += m_direction * (m_moveSpeed * deltaTime);
    rotation += m_rotationSpeed * deltaTime;
}
