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

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

#include "ObjectPool.hpp"
#include "Entity.hpp"

class Enemy : public Entity
{
private:
    static constexpr float DEFAULT_SPEED = 1.f;
    static constexpr float MIN_SPEED = 0.005f;
    static constexpr float BROOD_SPEED_REDUCTION = 0.65f;

    float m_speed;
    sf::Vector2f m_velocity;

public:
    Enemy(const sf::Vector2f& position)
        :Entity(position),m_speed(DEFAULT_SPEED) {}
	
    void draw(sf::RenderWindow& window)const;
    void update(float ratio);
    void update(GameState& gstate);
    void update(GameState& gstate, const sf::Vector2f& centroid, const sf::Vector2f& velocity);

    void getBoundingSpheres(BoundingSpheres& boundingSpheres)const;
    const sf::Vector2f& getVelocity()const { return m_velocity; }

    static constexpr float SIZE = 2;
};

#endif
