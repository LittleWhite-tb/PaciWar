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

#ifndef RADIALEXPLOSION_HPP
#define RADIALEXPLOSION_HPP

#include <SFML/Graphics.hpp>

class RadialExplosion
{
private:
    sf::Vector2f m_spawnPoint;
    float m_radius;

    static constexpr float RADIUS_MAX = 115;
    static constexpr float GROWTH_SPEED = 0.6f;

public:
    RadialExplosion(const sf::Vector2f& position)
        :m_spawnPoint(position),m_radius(0) {}

    void draw(sf::RenderWindow& window)const;
    void update(unsigned int time);
    bool isValid()const;

    float getRadius()const { return m_radius; }
    const sf::Vector2f& getCenter()const { return m_spawnPoint; }

    static constexpr float EFFECT_SIZE = 20;
};

#endif
