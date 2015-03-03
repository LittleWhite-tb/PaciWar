#include "ParticleSystem.hpp"

#include "RandomGenerator.hpp"

ParticleSystem::ParticleSystem(const sf::Vector2f& position)
    :m_spawnPoint(position),m_particles(ParticleSystem::MAX_PARTICULES),m_particlesAlive(ParticleSystem::MAX_PARTICULES),
     m_randomFloatDistribution(-1.0f,1.0f),m_randomSpeedDistribution(0.0f,2.f)
{
    for (size_t i = 0 ; i < ParticleSystem::MAX_PARTICULES ; ++i )
    {
        genParticle(i);
    }
}

void ParticleSystem::genParticle(size_t index)
{
    Particle p;

    p.position = m_spawnPoint;
    p.direction.x = m_randomFloatDistribution(RandomGenerator::get());
    p.direction.y = m_randomFloatDistribution(RandomGenerator::get());
    p.speed = m_randomSpeedDistribution(RandomGenerator::get());

    p.color.x = m_randomFloatDistribution(RandomGenerator::get());
    p.color.y = m_randomFloatDistribution(RandomGenerator::get());
    p.color.z = m_randomFloatDistribution(RandomGenerator::get());

    m_particles[index] = std::move(p);
}

void ParticleSystem::killParticle(size_t index)
{
    if ( m_particlesAlive > 0 )
    {
        std::swap(m_particles[index],m_particles[m_particlesAlive-1]);

        m_particlesAlive--;
    }
}

void ParticleSystem::draw(sf::RenderWindow& window)
{
    for (size_t i = 0 ; i < m_particlesAlive ; ++i)
    {
        sf::Vertex pV[] =
        {
            sf::Vertex(m_particles[i].position),
            sf::Vertex(m_particles[i].position-m_particles[i].direction*Particle::SIZE),
        };

        window.draw(pV,2,sf::Lines);
    }
}

void ParticleSystem::update(unsigned int time)
{
    for (size_t i = 0 ; i < m_particlesAlive ; ++i)
    {
        sf::Vector2f dir(m_particles[i].direction.x * m_particles[i].speed * time,
                         m_particles[i].direction.y * m_particles[i].speed * time);
        m_particles[i].position = m_particles[i].position + dir;
        m_particles[i].speed -= 0.01 * time;
        if ( m_particles[i].speed < 0 )
        {
            killParticle(i);
        }
    }
}
