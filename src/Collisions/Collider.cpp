#include "Collider.hpp"

#include "SFML/Vector2Utils.hpp"

#include "Player.hpp"
#include "Barrier.hpp"
#include "Enemy.hpp"

#include "Sphere.hpp"
#include "Line.hpp"

bool Collider::collides(const Sphere& s1, const Sphere& s2)
{
    // Pythagorian distance
    float distance = SFMLUtils::distance(s1.center,s2.center);
    if ( distance <= (s1.radius*s1.radius + s2.radius*s2.radius) )
    {
        return true;
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

CollisionResult Collider::collides(const Player& player, const Barrier& barrier)
{
    if ( Collider::collides(player.getBoundingSphere(), barrier.getLine()) )
    {
        return CollisionResult::BARRIER;
    }

    auto barrierSpheres = barrier.getBoundingSpheres();
    for (Sphere barrierSphere : barrierSpheres )
    {
        if ( Collider::collides(player.getBoundingSphere(),barrierSphere))
        {
            return CollisionResult::PLAYER;
        }
    }

    return CollisionResult::NONE;
}

bool Collider::collides(const Player& player, const Enemy& enemy)
{
    return collides(player.getBoundingSphere(), enemy.getBoundingSphere());
}
