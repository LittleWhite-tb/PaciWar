#ifndef ENGINEPARTICLESYSTEM_HPP
#define ENGINEPARTICLESYSTEM_HPP

#include "ParticleSystem.hpp"

#include <SFML/Graphics.hpp>

class EngineParticleSystem : public ParticleSystem
{
    static constexpr float PARTICLE_DISPERSION = 0.55;

private:
    bool m_enabled;
    sf::Vector2f m_direction;

    void generateParticles();

public:
    EngineParticleSystem(std::size_t nbMaxParticle=100);

    void update(const sf::Vector2f& position, const sf::Vector2f& direction, unsigned int time);
};

#endif
