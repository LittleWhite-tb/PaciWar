#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__

#include <SFML/Graphics.hpp>

struct Sphere
{
    sf::Vector2f center;
    float radius;

    Sphere(const sf::Vector2f& c, float r):
        center(c),radius(r) {}
};

#endif
