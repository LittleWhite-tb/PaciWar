#include "Particle.hpp"

void Particle::draw(sf::RenderWindow &window)
{
    sf::Vertex pV[] =
    {
        sf::Vertex(position,color),
        sf::Vertex(position-direction*size,color),
    };

    window.draw(pV,2,sf::Lines);
}

void Particle::update(unsigned int time)
{
    sf::Vector2f dir(direction.x * speed * time,
                     direction.y * speed * time);
    position = position + dir;
    speed -= accel * time;

}

bool Particle::isValid()const
{
    if ( speed < 0 )
    {
        return true;
    }

    return false;
}
