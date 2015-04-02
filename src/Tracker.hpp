#ifndef TRACKER_HPP
#define TRACKER_HPP

#include <SFML/Graphics.hpp>

class Entity;

class Tracker
{
public:
    static void update(sf::Vector2f& position, float &rotation, const Entity& target, float moveSpeed, float rotationSpeed, unsigned int deltaTime);
};

#endif
