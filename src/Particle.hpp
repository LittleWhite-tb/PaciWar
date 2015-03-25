#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

struct Particle
{
    static constexpr float SIZE = 4.0;

    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;

    sf::Color color;

    Particle(const sf::Vector2f& position,
             const sf::Vector2f& direction,
             const sf::Color& color,
             float speed)
             :position(position),direction(direction),color(color),
              speed(speed) {}


    void draw(sf::RenderWindow& window);
    void update(unsigned int time);
    bool isValid()const;
};

#endif
