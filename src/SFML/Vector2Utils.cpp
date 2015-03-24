#include "Vector2Utils.hpp"

#include <cassert>

float SFMLUtils::length(const sf::Vector2f& v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

void SFMLUtils::normalise(sf::Vector2f& v)
{
    float l = SFMLUtils::length(v);
    v.x = v.x/l;
    v.y = v.y/l;
}

float SFMLUtils::distance(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
    sf::Vector2f delta = v1 - v2;
    return delta.x*delta.x+delta.y*delta.y;
}

float SFMLUtils::getAngle(const sf::Vector2f& v)
{
    float angle = atan(v.y/v.x) * 180.f/M_PI;
    if ( v.x >= 0 ) // First quadrant, is ok
    {
        if ( v.y < 0 ) // Forth quadran
        {
            angle += 360;
        }
    }
    if ( (v.x < 0) ) // Second and third
    {
        angle += 180;
    }

    return angle;
}
