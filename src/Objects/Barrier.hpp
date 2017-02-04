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

#ifndef BARRIER_HPP
#define BARRIER_HPP

#include <SFML/Graphics.hpp>

#include "Collisions/Line.hpp"
#include "Entity.hpp"
#include "Actors/Momentum.hpp"

class Barrier : public Entity , public Named<Barrier>
{
private:
    static constexpr int barrierSize = 96;
    static constexpr float heightSize = Barrier::barrierSize/16.f;
    static constexpr float midSize = Barrier::barrierSize/2.f;
    static constexpr float edgeSize = Barrier::barrierSize/8.f;
    static constexpr float radius = 5.0f;

    // Object space position
    static const sf::Vector2f oj_leftEdgePosition;
    static const sf::Vector2f oj_rightEdgePosition;
    Momentum m_momentum;

    sf::Vector2f leftEdgePosition;
    sf::Vector2f rightEdgePosition;

    // static constexpr float ROTATION_SPEED = 0.015f;
    void updateEdgePosition();

public:
    static const std::string m_name;

public:
    Barrier(const sf::Vector2f& position);
	
    void draw(sf::RenderWindow& window)const;
    void debugDraw(sf::RenderWindow& window)const;

    void getBoundingSpheres(BoundingSpheres &boundingSpheres)const;
    Line getLine()const;

    void update(GameState& gstate);

    const sf::Vector2f& getLeftEdgePosition()const { return leftEdgePosition; }
    const sf::Vector2f& getRightEdgePosition()const { return rightEdgePosition; }
};

#endif
