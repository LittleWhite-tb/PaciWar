#include "FixedColorParticleSystem.hpp"

#include "RandomGenerator.hpp"

FixedColorParticleSystem::FixedColorParticleSystem(const sf::Vector2f& position, const sf::Color& color, std::size_t nbMaxParticle)
    :m_color(color),ParticleSystem(position)
{
    while (m_particles.nbAlive() != m_particles.capacity())
    {
        generateParticle();
    }
}

void FixedColorParticleSystem::generateParticle()
{
    m_particles.add(m_spawnPoint,
                    RandomGenerator::getNormalizedDirection(),
                    m_color,
                    RandomGenerator::getFloat(0.0,1.5),
                    0.006f);
}
