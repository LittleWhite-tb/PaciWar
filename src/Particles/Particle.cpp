#include "Particle.hpp"

void Particle::draw(sf::RenderWindow &window)const
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
    speed -= speed * accel * time;

    unsigned int hLifeTime = maxLife/2;
    float ratio = 255 / static_cast<float>(hLifeTime);
    if ( life > hLifeTime )
    {
        color.a = (maxLife - life) * ratio;
    }

    life += time;
}

bool Particle::isValid()const
{
    if ( life > maxLife )
    {
        return true;
    }

    return false;
}
