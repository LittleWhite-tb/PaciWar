#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity{
private:

protected:
    sf::Vector2f m_position;
    float m_rotation;

public:
    Entity(const sf::Vector2f& position)
        :m_position(position),m_rotation(0) {}

    virtual ~Entity() {}


    virtual void draw(sf::RenderWindow& window)=0;
    virtual void debugDraw(sf::RenderWindow& window) {}

    const sf::Vector2f& getPosition()const { return m_position; }
};

#endif
