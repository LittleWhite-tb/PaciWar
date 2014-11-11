#include "Vector2Utils.hpp"

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
