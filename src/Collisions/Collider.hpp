#ifndef __COLLIDER_HPP__
#define __COLLIDER_HPP__

class Sphere;
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
    static CollisionResult collides(const Player& player, const Barrier& barrier);
    static bool collides(const Player& player, const Enemy& enemy);
};

#endif
