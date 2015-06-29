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

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

struct Particle
{
    float size;

    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;

    float accel;

    unsigned int life;
    unsigned int maxLife;

    sf::Color color;

    Particle(const sf::Vector2f& position,
             const sf::Vector2f& direction,
             const sf::Color& color,
             float maxLife,
             float speed)
             :size(4),
              position(position),direction(direction),color(color),
              speed(speed),accel(0.01f),life(0),maxLife(maxLife) {}

    Particle(const sf::Vector2f& position,
             const sf::Vector2f& direction,
             const sf::Color& color,
             float maxLife,
             float speed,float acceleration)
             :size(4),
              position(position),direction(direction),color(color),
              speed(speed),accel(acceleration),
              life(0),maxLife(maxLife)
    {}

    void draw(sf::RenderWindow& window)const;
    void update(unsigned int time);
    bool isValid()const;
};

#endif
