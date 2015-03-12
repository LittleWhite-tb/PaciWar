#include "ParticleSystem.hpp"

#include "RandomGenerator.hpp"

#include <functional>

void ParticleSystem::Particle::draw(sf::RenderWindow &window)
{
    sf::Vertex pV[] =
    {
        sf::Vertex(position),
        sf::Vertex(position-direction*Particle::SIZE),
    };

    window.draw(pV,2,sf::Lines);
}

void ParticleSystem::Particle::update(unsigned int time)
{
    sf::Vector2f dir(direction.x * speed * time,
                     direction.y * speed * time);
    position = position + dir;
    speed -= 0.01 * time;

}

bool ParticleSystem::Particle::isValid()const
{
    if ( speed < 0 )
    {
        return true;
    }

    return false;
}

ParticleSystem::ParticleSystem(const sf::Vector2f& position)
    :m_spawnPoint(position),m_particles(ParticleSystem::MAX_PARTICULES)
{
    for (size_t i = 0 ; i < ParticleSystem::MAX_PARTICULES ; ++i )
    {
        genParticle();
    }
}

void ParticleSystem::genParticle()
{
    Particle p;

    p.position = m_spawnPoint;
    p.direction.x = RandomGenerator::getFloat(-1.0,1.0);
    p.direction.y = RandomGenerator::getFloat(-1.0,1.0);
    p.speed = RandomGenerator::getFloat(0.0,2.0);

    p.color.x = RandomGenerator::getFloat(-1.0,1.0);
    p.color.y = RandomGenerator::getFloat(-1.0,1.0);
    p.color.z = RandomGenerator::getFloat(0.0,2.0);

    m_particles.add(p);
}

void ParticleSystem::draw(sf::RenderWindow& window)
{

    m_particles.update(std::bind(&ParticleSystem::Particle::draw,
                                 std::placeholders::_1,
                                 std::ref(window)));
}

void ParticleSystem::update(unsigned int time)
{
    m_particles.update(std::bind(&ParticleSystem::Particle::update,
                                 std::placeholders::_1,
                                 time));
    m_particles.purge(std::bind(&ParticleSystem::Particle::isValid,
                                std::placeholders::_1));
}
