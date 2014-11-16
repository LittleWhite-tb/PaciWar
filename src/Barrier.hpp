#ifndef BARRIER_HPP
#define BARRIER_HPP

#include <SFML/Graphics.hpp>

#include "Collisions/Sphere.hpp"
#include "Collisions/Line.hpp"
#include "Entity.hpp"

class Barrier : public Entity
{
private:
    static const int barrierSize = 96;
    static const float heightSize;
    static const float midSize;
    static const float edgeSize;
    static const float radius;

    static const sf::Vector2f leftEdgePosition;
    static const sf::Vector2f rightEdgePosition;

    void getTransformedPoint(sf::Vector2f& transformedLeftEdgePosition,
                             sf::Vector2f& transformedRightEdgePosition) const;

    sf::Transform rotationTransform;

public:
    Barrier(const sf::Vector2f& position);
	
	void draw(sf::RenderWindow& window);
    void debugDraw(sf::RenderWindow& window);

    std::vector<Sphere> getBoundingSpheres()const;
    Line getLine()const;

    void update(unsigned int time);
};

#endif
