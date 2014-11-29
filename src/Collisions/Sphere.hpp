#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__

#include <SFML/Graphics.hpp>

#include <vector>

struct Sphere
{
    sf::Vector2f center;
    float radius;

    Sphere(const sf::Vector2f& c, float r):
        center(c),radius(r) {}
    Sphere():
        center(sf::Vector2f(0,0)),radius(0) {}
};

typedef std::vector<Sphere> BoundingSpheres;

#endif
