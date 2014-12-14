#ifndef __COLLIDER_HPP__
#define __COLLIDER_HPP__

#include "Sphere.hpp"

class Line;
class Player;
class Barrier;
class Enemy;

enum CollisionResult
{
    NONE,
    PLAYER,
    BARRIER
};

class Collider
{
private:
    static bool collides(const Sphere& s1, const Sphere& s2);
    static bool collides(const Sphere& s, const Line& l);

public:
    static bool collides(const BoundingSpheres& bs1, const BoundingSpheres& bs2);

    static CollisionResult collides(const Player& player, const Barrier& barrier);
    static CollisionResult collides(const Player& player, const Enemy& enemy);
};

#endif
