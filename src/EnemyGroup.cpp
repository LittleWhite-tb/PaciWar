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

#include "EnemyGroup.hpp"

#include "Math/Vector2.hpp"
#include "Objects/Enemy.hpp"
#include "GameState.hpp"

#include <cassert>

std::vector<sf::Color> groupColors = {
    { 255, 0, 0 },
    { 255, 255, 0 },
    { 255, 0, 255 },
    { 0, 0, 255 },
    { 0, 255, 255 },
    };

EnemyGroup::EnemyGroup(Enemy* first, const sf::Color& color)
{
    assert(first);
    m_enemies.push_back(first);
    first->setColor(color);
    m_position = first->getPosition();
    m_color = color;
}

bool EnemyGroup::integrate(Enemy* candidate)
{
    if(candidate == nullptr)
    {
        assert(false); // Why are we passing nullptr here
        return false;
    }

    auto accepted = Math::distance(candidate->getPosition(), m_position) < this->influenceRadius * this->influenceRadius;
    if (!accepted)
    {
        return false;
    }

    m_enemies.push_back(candidate);
    m_position.x = (m_position.x * (m_enemies.size()-1) + candidate->getPosition().x) / m_enemies.size();
    m_position.y = (m_position.y * (m_enemies.size()-1) + candidate->getPosition().y) / m_enemies.size();
    candidate->setColor(m_color);
    return true;
}

void EnemyGroup::update(GameState& gstate)
{
    auto origin = m_position;
    auto dir = gstate.getObjects().getPlayer().getPosition() - origin;
    Math::normalise(dir);

    std::for_each(m_enemies.begin(), m_enemies.end(), [&dir](Enemy* e){

        e->update(dir);
    });
}

void EnemyGroups::classify(Enemy& enemy)
{
    bool accepted = false;
    for(auto& g : m_groups)
    {
        accepted = g.integrate(&enemy);
        if (accepted)
        {
            break;
        }
    }

    if(!accepted)
    {
        m_groups.emplace_back(&enemy, groupColors[m_groups.size() % groupColors.size()]);
    }
}

void EnemyGroups::reset()
{
    m_groups.clear();
}

void EnemyGroups::update(GameState& gstate)
{
    std::for_each(m_groups.begin(), m_groups.end(), [&gstate](EnemyGroup& g){ g.update(gstate); });
}
