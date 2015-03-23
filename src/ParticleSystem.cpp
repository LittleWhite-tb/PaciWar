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
        m_particles.add(m_spawnPoint,
                        sf::Vector2f(RandomGenerator::getFloat(-1.0,1.0),RandomGenerator::getFloat(-1.0,1.0)),
                        sf::Vector3f(RandomGenerator::getFloat(-1.0,1.0),RandomGenerator::getFloat(-1.0,1.0),RandomGenerator::getFloat(-1.0,1.0)),
                        RandomGenerator::getFloat(0.0,2.0));
    }
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
