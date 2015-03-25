#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "ObjectPool.hpp"
#include "RandomGenerator.hpp"

#include "Particle.hpp"
#include "ParticleSpawners.hpp"

template <typename ParticleSpawner>
class ParticleSystem : private ParticleSpawner
{
    using ParticleSpawner::spawnParticles;

private:
    sf::Vector2f m_spawnPoint;

    Pool<Particle> m_particles;

public:
    ParticleSystem(const sf::Vector2f& position, std::size_t nbMaxParticle = 100)
        :m_spawnPoint(position),m_particles(nbMaxParticle)
    {
        spawnParticles(m_particles,m_spawnPoint);
    }

    void draw(sf::RenderWindow& window)
    {

        m_particles.update(std::bind(&Particle::draw,
                                     std::placeholders::_1,
                                     std::ref(window)));
    }

    void update(unsigned int time)
    {
        m_particles.update(std::bind(&Particle::update,
                                     std::placeholders::_1,
                                     time));
        m_particles.purge(std::bind(&Particle::isValid,
                                    std::placeholders::_1));
    }

    std::size_t numberParticlesAlive()const { return m_particles.nbAlive(); }
    bool isDead()const { return m_particles.nbAlive() == 0; }
};

using ExplosionParticleSystem = ParticleSystem<InstantSphericalParticleSpawner>;

#endif
