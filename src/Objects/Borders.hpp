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

#ifndef BORDERS_HPP
#define BORDERS_HPP

#include <SFML/Graphics.hpp>

class Entity;

class Borders
{
    static constexpr float GAP = 1.5f;
    static constexpr float GRID_REDUCTION = 50.f;
    static constexpr unsigned int IMPULSE_TIME = 750;

    static const sf::Color normalColor;

    typedef unsigned int Location;
    static constexpr Location LEFT = 1;
    static constexpr Location TOP = 2;
    static constexpr Location RIGHT = 4;
    static constexpr Location DOWN = 8;

private:
    sf::IntRect m_restrictedLimits;
    sf::IntRect m_outerLimits;
    sf::IntRect m_innerLimits;
    int m_impulseCounter;
    sf::Color m_impulseColor;

    Location getCollisionLocation(const sf::Vector2f& position, float offset=0)const;

public:
    Borders(const sf::IntRect& limits)
        :m_restrictedLimits(limits.left+GRID_REDUCTION,
                            limits.top+GRID_REDUCTION,
                            limits.width-GRID_REDUCTION*2,
                            limits.height-GRID_REDUCTION*2),
          m_outerLimits(limits.left-GAP,
                        limits.top-GAP,
                        limits.width+GAP*2,
                        limits.height+GAP*2),

          m_innerLimits(limits.left+GAP,
                        limits.top+GAP,
                        limits.width-GAP*2,
                        limits.height-GAP*2),
         m_impulseCounter(0) {}

    void draw(sf::RenderWindow& window)const;
    void update(unsigned int deltaTime);

    bool isOutside(const sf::Vector2f& position);
    bool isOutside(const Entity& entity);

    void clamp(const sf::Vector2f& position, sf::Vector2f& direction, float offset=0)const;
    void bounce(const sf::Vector2f& position, sf::Vector2f& direction, float offset=0)const;

    void impulse(const sf::Color& impulseColor);

    sf::IntRect getRestrictedLimits()const { return m_restrictedLimits; }
};

#endif
