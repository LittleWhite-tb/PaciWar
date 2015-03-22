#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

#include "Collisions/Sphere.hpp"

class Entity{
private:

protected:
    sf::Vector2f m_position;
    float m_rotation;

    bool m_dead;

public:
    Entity(const sf::Vector2f& position)
        :m_position(position),m_rotation(0),m_dead(false) {}

    virtual ~Entity() {}


    virtual void draw(sf::RenderWindow& window)=0;
    virtual void debugDraw(sf::RenderWindow& window) {}

    const sf::Vector2f& getPosition()const { return m_position; }
    bool isDead()const { return m_dead; }
    void kill() { m_dead = true; }

    virtual void getBoundingSpheres(BoundingSpheres& boundingSpheres)const=0;
};

#endif
