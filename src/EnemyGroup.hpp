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

#ifndef ENEMYGROUP_HPP
#define ENEMYGROUP_HPP

#include <vector>

#include <SFML/Graphics.hpp>

class Enemy;
class GameState;

class EnemyGroup
{
    static constexpr unsigned int influenceRadius= 30;

public:
    EnemyGroup(Enemy* first, const sf::Color& color);

    bool integrate(Enemy* candidate);
    void update(GameState& gstate);

private:
    std::vector<Enemy*> m_enemies;
    sf::Vector2f m_position;
    sf::Color m_color;
};

class EnemyGroups
{
public:
    void classify(Enemy& enemy);
    void reset();
    void update(GameState& gstate);

private:
    std::vector<EnemyGroup> m_groups;
};

#endif
