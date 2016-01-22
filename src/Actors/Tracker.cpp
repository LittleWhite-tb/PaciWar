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

#include "Tracker.hpp"

#include "Objects/Entity.hpp"

#include "Math/Vector2.hpp"
#include "Math/Interpolation.hpp"
#include "Math/constants.hpp"

void Tracker::update(sf::Vector2f& position, float& rotation, const Entity &target, float moveSpeed, float rotationSpeed, unsigned int deltaTime)
{
    sf::Vector2f targetDir = target.getPosition() - position;

    float targetRotation = Math::getAngle(targetDir);
    rotation = Math::EaseInEaseOut<Math::Angle<float> >::get(rotation,targetRotation,rotationSpeed);

    sf::Vector2f dir;
    if ( Math::length(targetDir) > 5 )
    {
         dir = Math::getVectorFromAngle(rotation);
         position = position + dir * (moveSpeed * deltaTime);
    }
    else
    {
        position = target.getPosition();
    }

}
