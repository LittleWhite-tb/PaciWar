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

#include "Collider.hpp"

#include <cmath>

#include "Math/Vector2.hpp"

#include "Objects/Player.hpp"
#include "Objects/Barrier.hpp"
#include "Objects/Enemy.hpp"
#include "Objects/RadialExplosion.hpp"

#include "Sphere.hpp"
#include "Line.hpp"

static const CollisionResult NoCollision = CollisionResult();
static const BarrierCollisionResult NoBarrierCollision = BarrierCollisionResult();

bool Collider::collides(const Sphere& s1, const Sphere& s2)
{
    // Pythagorian distance
    float distance = Math::distance(s1.center,s2.center);
    if ( distance <= std::pow(s1.radius + s2.radius,2) )
    {
        return true;
    }
    return false;
}

bool Collider::collides(const BoundingSpheres& bs1, const BoundingSpheres& bs2)
{
    for (const Sphere& s1 : bs1 )
    {
        for (const Sphere& s2 : bs2)
        {
            if (Collider::collides(s1,s2))
            {
                return true;
            }
        }
    }
    return false;
}

float dot(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

bool Collider::collides(const Sphere& s, const Line& l)
{
    // http://stackoverflow.com/questions/1073336/circle-line-collision-detection
    sf::Vector2f dir = l.end - l.start;
    sf::Vector2f f = l.start - s.center;

    // Quadratic equation
    float a = dot(dir, dir);
    float b = 2 * dot(f, dir);
    float c = dot(f, f) - s.radius*s.radius;

    float discriminant = b*b-4*a*c;
    if( discriminant < 0 )
    {
        return false;
    }
    else
    {
        // ray didn't totally miss sphere, so there is a solution to
        // the equation.
        discriminant = sqrt( discriminant );

        // either solution may be on or off the ray so need to test both
        // t1 is always the smaller value, because BOTH discriminant and
        // a are nonnegative.
        float t1 = (-b - discriminant)/(2*a);
        float t2 = (-b + discriminant)/(2*a);

        // 3x HIT cases:
        //          -o->             --|-->  |            |  --|->
        // Impale(t1 hit,t2 hit), Poke(t1 hit,t2>1), ExitWound(t1<0, t2 hit),

        // 3x MISS cases:
        //       ->  o                     o ->              | -> |
        // FallShort (t1>1,t2>1), Past (t1<0,t2<0), CompletelyInside(t1<0, t2>1)
        if( t1 >= 0 && t1 <= 1 )
        {
            // t1 is the intersection, and it's closer than t2
            // (since t1 uses -b - discriminant)
            // Impale, Poke
            return true ;
        }

        // here t1 didn't intersect so we are either started
        // inside the sphere or completely past it
        if( t2 >= 0 && t2 <= 1 )
        {
            return true ;
        }

        // no intn: FallShort, Past, CompletelyInside
        return false ;
    }
}

bool Collider::collides(const Line& l1, const Line& l2)
{
    // Check for parallel
    sf::Vector2f vector1 = l1.end - l1.start;
    sf::Vector2f vector2 = l2.end - l2.start;
    if ( l1.start.y/l1.start.x != l2.start.y/l2.start.x )
    {
        float d = vector1.x * vector2.y - vector1.y * vector2.x;
        if ( d != 0 )
        {
            sf::Vector2f vertor3 = l1.start - l2.start;
            float r = (vertor3.y * vector2.x - vertor3.x * vector2.y) / d;
            float s = (vertor3.y * vector1.x - vertor3.x * vector1.y) / d;
            if ( r >= 0 && r <= 1 && s >= 0 && s <= 1 )
            {
                return true;
            }
        }
    }
    return false;
}

BarrierCollisionResult Collider::collides(const Player& player, const Barrier& barrier)
{
    BoundingSpheres playerBoundingSpheres;
    player.getBoundingSpheres(playerBoundingSpheres);

    BoundingSpheres barrierBoundingSpheres;
    barrier.getBoundingSpheres(barrierBoundingSpheres);
    if ( Collider::collides(playerBoundingSpheres,barrierBoundingSpheres)) // The barrier kills the player, first
    {
        return BarrierCollisionResult(&player,&barrier, BarrierCollisionResult::PLAYER);
    }


    if ( Collider::collides(playerBoundingSpheres[0], barrier.getLine()))
    {
        return BarrierCollisionResult(&player, &barrier, BarrierCollisionResult::BARRIER);
    }

    return NoBarrierCollision;
}

CollisionResult Collider::collides(const Player& player, const Entity& entity)
{
    BoundingSpheres playerBoundingSpheres;
    player.getBoundingSpheres(playerBoundingSpheres);

    BoundingSpheres entityBoundingSpheres;
    entity.getBoundingSpheres(entityBoundingSpheres);
    if ( collides(playerBoundingSpheres, entityBoundingSpheres) )
    {
        return CollisionResult(&player, &entity);
    }
    return NoCollision;
}

CollisionResult Collider::collides(const Enemy &enemy, const RadialExplosion &explosion)
{
    BoundingSpheres enemyBoundingSpheres;
    enemy.getBoundingSpheres(enemyBoundingSpheres);

    for (const Sphere& s : enemyBoundingSpheres )
    {
        float distance = Math::distance(s.center,explosion.getCenter());
        if ( distance < std::pow(explosion.getRadius(),2))
        {
            return CollisionResult(&enemy,nullptr); // HACK : Using nullptr is really big hack and will cause some bugs
        }
    }

    return NoCollision;
}
