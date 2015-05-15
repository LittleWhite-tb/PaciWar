#include "ParticleSystem.hpp"

#include "Utils/RandomGenerator.hpp"

ParticleSystem::ParticleSystem(const sf::Vector2f& position, std::size_t nbMaxParticle)
    :m_spawnPoint(position),m_particles(nbMaxParticle)
{
    // generateParticles();
}

void ParticleSystem::generateParticle()
{
    m_particles.add(m_spawnPoint,
                    RandomGenerator::getNormalizedDirection(),
                    RandomGenerator::getColor(100,255),
                    RandomGenerator::getFloat(0.0,2.0));
}

void ParticleSystem::draw(sf::RenderWindow& window) const
{
    std::for_each(m_particles.cbegin(),m_particles.cend(), [&window](const Particle& p){ p.draw(window); });
}

void ParticleSystem::update(unsigned int time)
{
    std::for_each(m_particles.begin(),m_particles.end(), [time](Particle& p){ p.update(time); });
    m_particles.purge(std::bind(&Particle::isValid,
                                std::placeholders::_1));
}
