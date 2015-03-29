#include "FixedColorParticleSystem.hpp"

#include "RandomGenerator.hpp"

FixedColorParticleSystem::FixedColorParticleSystem(const sf::Vector2f& position, const sf::Color& color, std::size_t nbMaxParticle)
    :m_color(color),ParticleSystem(position)
{
    generateParticles();
}

void FixedColorParticleSystem::generateParticles()
{
    while (m_particles.nbAlive() != m_particles.capacity())
    {
        m_particles.add(m_spawnPoint,
                        sf::Vector2f(RandomGenerator::getFloat(-1.0,1.0),RandomGenerator::getFloat(-1.0,1.0)),
                        m_color,
                        RandomGenerator::getFloat(0.0,2.0));
    }
}
