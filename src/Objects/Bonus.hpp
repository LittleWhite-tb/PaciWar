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

#ifndef BONUS_HPP
#define BONUS_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

#include "Actors/Momentum.hpp"

class GameState;

class Bonus : public Entity, public Named<Bonus>
{
private:
    static constexpr float SPEED = 0.53f;              // Should be a bit greater than Player::SPEED otherwise
                                                        // you can't get them
    static constexpr unsigned int LIFETIME = 4000;
    static constexpr unsigned int MAGNET_DISTANCE = 60; // Should be a bit smaller than RadialExplosion::RADIUS_MAX
                                                        // to keep player going back to get these and take risk

    static constexpr unsigned int BLINK_TIME = 1000;
    static constexpr unsigned int BLINK_DELAY = 200;

    static const sf::Color normalColor;
    static const sf::Color lightColor;

    sf::Color m_color;

    int m_life;

    Momentum m_momentum;

public:
    static const std::string m_name;

public:
    Bonus(const sf::Vector2f& position);

    void draw(sf::RenderWindow& window)const;
    void update(GameState& gstate);

    void getBoundingSpheres(BoundingSpheres& boundingSpheres)const;

    static constexpr float SIZE = 1;

    bool isDead()const { return m_life < 0 || m_dead; }
};

#endif
