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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

#include "Object.hpp"
#include "Collisions/Sphere.hpp"

class GameState;

/**
 * @brief Entity is an item of the game. Hence it has a position and a rotation and has an alive status.
 * Also, it can be drawn and updated.
 * This class should not exists
 */
class Entity : public Object {
private:

protected:
    sf::Vector2f m_origin;
    sf::Vector2f m_destination;
    sf::Vector2f m_position;
    float m_rotation;

    bool m_dead;

public:
    Entity(const std::string& classId, const sf::Vector2f& position);
    virtual ~Entity() {}


    virtual void draw(sf::RenderWindow& window)const=0;
    virtual void debugDraw(sf::RenderWindow& window)const {}

    virtual void update(GameState& gstate)=0;

    const sf::Vector2f& getPosition()const { return m_position; }
    bool isDead()const { return m_dead; }
    void kill() { m_dead = true; }

    virtual void getBoundingSpheres(BoundingSpheres& boundingSpheres)const=0;
};

#endif
