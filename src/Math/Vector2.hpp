#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <SFML/Graphics.hpp>

// TODO Make this class handling all Vector2
namespace Math
{
    float length(const sf::Vector2f& v);
    void normalise(sf::Vector2f& v);
    float distance(const sf::Vector2f& v1, const sf::Vector2f& v2);

    float getAngle(const sf::Vector2f& v);
    sf::Vector2f getVectorFromAngle(float angle); // in degrees
}

#endif
