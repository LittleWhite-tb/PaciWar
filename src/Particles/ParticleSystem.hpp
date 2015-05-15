#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "ObjectPool.hpp"

#include "Particle.hpp"

class ParticleSystem
{
protected:
    sf::Vector2f m_spawnPoint;

    Pool<Particle> m_particles;

    virtual void generateParticle();

public:
    ParticleSystem(const sf::Vector2f& position, std::size_t nbMaxParticle=100);
    virtual ~ParticleSystem() {}

    virtual void draw(sf::RenderWindow& window)const;
    virtual void update(unsigned int time);

    std::size_t numberParticlesAlive()const { return m_particles.nbAlive(); }
    bool isDead()const { return m_particles.nbAlive() == 0; }
};

#endif
