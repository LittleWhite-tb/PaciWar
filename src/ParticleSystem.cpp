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
    :m_spawnPoint(position),m_particles(ParticleSystem::MAX_PARTICULES),
     m_randomFloatDistribution(-1.0f,1.0f),m_randomSpeedDistribution(0.0f,2.f)
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
    p.direction.x = m_randomFloatDistribution(RandomGenerator::get());
    p.direction.y = m_randomFloatDistribution(RandomGenerator::get());
    p.speed = m_randomSpeedDistribution(RandomGenerator::get());

    p.color.x = m_randomFloatDistribution(RandomGenerator::get());
    p.color.y = m_randomFloatDistribution(RandomGenerator::get());
    p.color.z = m_randomFloatDistribution(RandomGenerator::get());

    m_particles.add(p);
}

void ParticleSystem::draw(sf::RenderWindow& window)
{

    m_particles.apply(std::bind(&ParticleSystem::Particle::draw,
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
