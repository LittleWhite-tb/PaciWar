#include "EngineParticleSystem.hpp"

#include "RandomGenerator.hpp"
#include "Palette.hpp"

EngineParticleSystem::EngineParticleSystem(std::size_t nbMaxParticle)
    :ParticleSystem(sf::Vector2f(0,0),nbMaxParticle),
     m_enabled(false),m_direction(0,0),m_rainbowGradient(0),m_remaining_birth_time(0)
{

}

void EngineParticleSystem::generateParticle()
{
    sf::Color particleColor = Palette::fromHSV(m_rainbowGradient,1,1);
    sf::Vector2f startDirectionRange = { m_direction.x - PARTICLE_DISPERSION, m_direction.y - PARTICLE_DISPERSION };
    sf::Vector2f endDirectionRange = { m_direction.x + PARTICLE_DISPERSION, m_direction.y + PARTICLE_DISPERSION };

    {
        // Relies on the fact that the pool will never extend
        m_particles.add(m_spawnPoint,
                        RandomGenerator::getFloatVector(startDirectionRange.x,endDirectionRange.x,startDirectionRange.y,endDirectionRange.y),
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
        m_rainbowGradient+=time*GRADIENT_SPEED;

        time += m_remaining_birth_time;
        while ( time > BIRTH_PERIOD )
        {
            generateParticle();
            time-=BIRTH_PERIOD;
        }
        m_remaining_birth_time = time;
    }
}
