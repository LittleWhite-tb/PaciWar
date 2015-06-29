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

#ifndef ENEMYDEATH_HPP
#define ENEMYDEATH_HPP

#include <array>

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class GameState;
class Enemy;

class EnemyDeath : public Entity
{
private:
    struct Line
    {
        sf::Vector2f center;
        float rotation;

        sf::Vector2f moveDirectionBias;
        float moveSpeed;

        float rotationSpeed;

        Line(const sf::Vector2f& center, float rotation);

        void draw(sf::RenderWindow& window, const sf::Color& color)const;
    };

    std::array<Line,4> m_lines;
    long unsigned int m_lifeTime;

    static const sf::Color baseColor;
    static constexpr long unsigned int DURATION = 1250;
    static constexpr long unsigned int HDURATION = DURATION/2;

public:
    EnemyDeath(const sf::Vector2f& position);

    void draw(sf::RenderWindow& window) const;
    void update(GameState& gstate);

    bool isDead()const { return m_lifeTime > DURATION; }

    void getBoundingSpheres(BoundingSpheres& boundingSpheres)const {}
};

#endif
