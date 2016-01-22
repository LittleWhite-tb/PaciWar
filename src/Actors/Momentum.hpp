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

#ifndef MOMENTUM_HPP
#define MOMENTUM_HPP

#include <SFML/Graphics.hpp>

class Momentum
{
private:
    sf::Vector2f m_direction;
    float m_moveSpeed;
    float m_rotationSpeed;

public:
    Momentum();
    Momentum(float maxMoveSpeed, float maxRotationSpeed);
    Momentum(const sf::Vector2f& direction, float moveSpeed, float rotationSpeed);

    void update(sf::Vector2f& position, float& rotation, unsigned int deltaTime);

    const sf::Vector2f& getDirection()const { return m_direction; }
    void updateDirection(const sf::Vector2f& newDirection) { m_direction = newDirection; }
};

#endif
