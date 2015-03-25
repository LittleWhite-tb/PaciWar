#ifndef PARTICLESPAWNERS_HPP
#define PARTICLESPAWNERS_HPP

#include <SFML/Graphics.hpp>

#include "ObjectPool.hpp"
#include "RandomGenerator.hpp"

class InstantSphericalParticleSpawner
{
protected:
    template <typename ParticleType>
    void spawnParticles(Pool<ParticleType>& particles, const sf::Vector2f& spawnPoint)
    {
        while (particles.nbAlive() != particles.capacity())
        {
            particles.add(spawnPoint,
                          sf::Vector2f(RandomGenerator::getFloat(-1.0,1.0),RandomGenerator::getFloat(-1.0,1.0)),
                          sf::Color(RandomGenerator::getInt(100,255),RandomGenerator::getInt(100,255),RandomGenerator::getInt(100,255)),
                          RandomGenerator::getFloat(0.0,2.0));
        }
    }
};

#endif
