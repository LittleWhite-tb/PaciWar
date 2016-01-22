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

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

#include "Particles/EngineParticleSystem.hpp"

class Player : public Entity
{
private:
    static constexpr float SPEED = 0.5f;
    static constexpr float RADIUS = 6.0f;

    EngineParticleSystem m_engineParticles;
	
public:
    Player();
	
    void draw(sf::RenderWindow& window)const;
    void debugDraw(sf::RenderWindow& window)const;

    void update(GameState& gstate);

    void getBoundingSpheres(BoundingSpheres& boundingSpheres)const;
};

#endif
