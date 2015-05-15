#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

struct Particle
{
    float size;

    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;

    float accel;

    sf::Color color;

    Particle(const sf::Vector2f& position,
             const sf::Vector2f& direction,
             const sf::Color& color,
             float speed)
             :size(4),
              position(position),direction(direction),color(color),
              speed(speed),accel(0.01f) {}

    Particle(const sf::Vector2f& position,
             const sf::Vector2f& direction,
             const sf::Color& color,
             float speed,float acceleration)
             :size(4),
              position(position),direction(direction),color(color),
              speed(speed),accel(acceleration) {}

    void draw(sf::RenderWindow& window)const;
    void update(unsigned int time);
    bool isValid()const;
};

#endif
