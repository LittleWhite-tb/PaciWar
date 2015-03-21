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

public:
    static bool collides(const BoundingSpheres& bs1, const BoundingSpheres& bs2);

    static BarrierCollisionResult collides(const Player& player, const Barrier& barrier);
    static CollisionResult collides(const Player& player, const Enemy& enemy);
    static CollisionResult collides(const Enemy& enemy, const RadialExplosion& explosion);
};

#endif
