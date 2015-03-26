#include "ParticleSystem.hpp"

#include "RandomGenerator.hpp"

ParticleSystem::ParticleSystem(const sf::Vector2f& position, std::size_t nbMaxParticle)
    :m_spawnPoint(position),m_particles(nbMaxParticle)
{
    generateParticles();
}

void ParticleSystem::generateParticles()
{
    while (m_particles.nbAlive() != m_particles.capacity())
    {
        m_particles.add(m_spawnPoint,
                        sf::Vector2f(RandomGenerator::getFloat(-1.0,1.0),RandomGenerator::getFloat(-1.0,1.0)),
                        sf::Color(RandomGenerator::getInt(100,255),RandomGenerator::getInt(100,255),RandomGenerator::getInt(100,255)),
                        RandomGenerator::getFloat(0.0,2.0));
    }
}

void ParticleSystem::draw(sf::RenderWindow& window)
{
    m_particles.update(std::bind(&Particle::draw,
                                 std::placeholders::_1,
                                 std::ref(window)));
}

void ParticleSystem::update(unsigned int time)
{
    m_particles.update(std::bind(&Particle::update,
                               std::placeholders::_1,
                               time));
    m_particles.purge(std::bind(&Particle::isValid,
                              std::placeholders::_1));
}
