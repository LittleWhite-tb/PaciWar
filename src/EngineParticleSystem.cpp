#include "EngineParticleSystem.hpp"

#include "RandomGenerator.hpp"
#include "Palette.hpp"

EngineParticleSystem::EngineParticleSystem(std::size_t nbMaxParticle)
    :ParticleSystem(sf::Vector2f(0,0),nbMaxParticle),
     m_enabled(false),m_direction(0,0),rainbowGradient(0)
{

}

void EngineParticleSystem::generateParticles()
{
    sf::Color particleColor = Palette::fromHSV(rainbowGradient,1,1);
    sf::Vector2f startDirectionRange = { m_direction.x - PARTICLE_DISPERSION, m_direction.y - PARTICLE_DISPERSION };
    sf::Vector2f endDirectionRange = { m_direction.x + PARTICLE_DISPERSION, m_direction.y + PARTICLE_DISPERSION };

    // while (m_particles.nbAlive() != m_particles.capacity())
    {
        m_particles.add(m_spawnPoint,
                        sf::Vector2f(RandomGenerator::getFloat(startDirectionRange.x,endDirectionRange.x),RandomGenerator::getFloat(startDirectionRange.y,endDirectionRange.y)),
                        particleColor,
                        0.1f,0.0002f);
    }
}

void EngineParticleSystem::update(const sf::Vector2f &position, const sf::Vector2f &direction, unsigned int time)
{
    ParticleSystem::update(time);

    // Add particules with updated settings
    m_spawnPoint = position;
    m_direction = direction;
    m_enabled = !(direction.x == 0 && direction.y == 0); // Only enabled the direction is valid

    if (m_enabled)
    {
        rainbowGradient+=time*GRADIENT_SPEED;
        generateParticles();
    }
}
