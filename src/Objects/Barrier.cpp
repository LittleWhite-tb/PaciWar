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

#include "Barrier.hpp"

#include "GameState.hpp"

constexpr int Barrier::barrierSize;
constexpr float Barrier::heightSize;
constexpr float Barrier::midSize;
constexpr float Barrier::edgeSize;
constexpr float Barrier::radius;

const sf::Vector2f Barrier::oj_leftEdgePosition = sf::Vector2f(-midSize+Barrier::edgeSize/2.0f,0);
const sf::Vector2f Barrier::oj_rightEdgePosition = sf::Vector2f(midSize-Barrier::edgeSize/2.0f,0);

const std::string Barrier::m_name = "Barrier";

Barrier::Barrier(const sf::Vector2f& position)
    :Entity("Barrier",position)
{
    updateEdgePosition();
}

void Barrier::updateEdgePosition()
{
    sf::Transform rotationMatrix;
    rotationMatrix.rotate(m_rotation);

    leftEdgePosition = rotationMatrix.transformPoint(oj_leftEdgePosition) + m_position;
    rightEdgePosition = rotationMatrix.transformPoint(oj_rightEdgePosition) + m_position;
}
	
void Barrier::draw(sf::RenderWindow& window) const
{
    const sf::Vertex lines[] =
	{
        sf::Vertex(sf::Vector2f(-midSize, 0)),
        sf::Vertex(sf::Vector2f(-midSize+edgeSize, -heightSize)),
        sf::Vertex(sf::Vector2f(-midSize+edgeSize, heightSize)),
        sf::Vertex(sf::Vector2f(-midSize, 0)),
        sf::Vertex(sf::Vector2f(midSize, 0)),
        sf::Vertex(sf::Vector2f(midSize-edgeSize, -heightSize)),
        sf::Vertex(sf::Vector2f(midSize-edgeSize, heightSize)),
        sf::Vertex(sf::Vector2f(midSize, 0))
	};

    sf::Transform t;
    t.translate(m_position);
    t.rotate(m_rotation);

    window.draw(lines,8 ,sf::LinesStrip,t);
}

void Barrier::debugDraw(sf::RenderWindow& window) const
{
    sf::CircleShape debugCircle(Barrier::radius);
    debugCircle.setFillColor(sf::Color::Transparent);
    debugCircle.setOutlineThickness(1);
    debugCircle.setOutlineColor(sf::Color(0,255,0));

    debugCircle.setPosition(leftEdgePosition + sf::Vector2f(-Barrier::radius,-Barrier::radius));

    window.draw(debugCircle);

    debugCircle.setPosition(rightEdgePosition + sf::Vector2f(-Barrier::radius,-Barrier::radius));

    window.draw(debugCircle);
}

void Barrier::getBoundingSpheres(BoundingSpheres &boundingSpheres)const
{
    boundingSpheres.push_back(Sphere(leftEdgePosition, Barrier::radius));
    boundingSpheres.push_back(Sphere(rightEdgePosition, Barrier::radius));
}

Line Barrier::getLine()const
{
    return Line(leftEdgePosition,rightEdgePosition);
}

void Barrier::update(GameState &gstate)
{
    m_momentum.update(m_position,m_rotation,gstate.getTime().getElapsedTime());

    updateEdgePosition();

    // Bounce against the grid
    sf::Vector2f direction = m_momentum.getDirection();

    gstate.getBorders().bounce(m_position,direction);
    gstate.getBorders().bounce(leftEdgePosition,direction,Barrier::radius);
    gstate.getBorders().bounce(rightEdgePosition,direction,Barrier::radius);

    m_momentum.updateDirection(direction);
}
