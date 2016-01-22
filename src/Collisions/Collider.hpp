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

#ifndef __COLLIDER_HPP__
#define __COLLIDER_HPP__

#include "Sphere.hpp"

class Line;
class Player;
class Barrier;
class Enemy;
class Entity;

class RadialExplosion;

class CollisionResult
{
public:
    bool collided;
    const Entity* const elem1;
    const Entity* const elem2;

    CollisionResult()
        :collided(false),elem1(nullptr),elem2(nullptr) {}
    CollisionResult(const Entity* const elem1, const Entity* const elem2)
        :collided(true),elem1(elem1),elem2(elem2) {}
};

class BarrierCollisionResult : public CollisionResult
{
public:
    enum Loser
    {
        PLAYER,
        BARRIER,
        NONE // Should not be on if collided == false
    };

private:
    Loser loser;

public:
    BarrierCollisionResult():
        CollisionResult(),loser(NONE) {}
    BarrierCollisionResult(const Entity* const elem1, const Entity* const elem2,
                           Loser loser)
        :CollisionResult(elem1,elem2),loser(loser) {}

    bool getLoser()const { return loser; }
};

class Collider
{
private:
    static bool collides(const Sphere& s1, const Sphere& s2);
    static bool collides(const Sphere& s, const Line& l);
    static bool collides(const Line& l1, const Line& l2);

public:
    static bool collides(const BoundingSpheres& bs1, const BoundingSpheres& bs2);

    static BarrierCollisionResult collides(const Player& player, const Barrier& barrier);
    static CollisionResult collides(const Player& player, const Entity &entity);
    static CollisionResult collides(const Enemy& enemy, const RadialExplosion& explosion);
};

#endif
